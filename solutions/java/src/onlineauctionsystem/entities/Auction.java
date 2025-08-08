package onlineauctionsystem.entities;

import onlineauctionsystem.enums.AuctionStatus;
import onlineauctionsystem.observer.AuctionObserver;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class Auction {
    private final String id;
    private final String itemName;
    private final String description;
    private final BigDecimal startingPrice;
    private final LocalDateTime endTime;

    private final List<Bid> bids;
    private final Set<AuctionObserver> observers;
    private AuctionStatus state;
    private Bid winningBid;

    public Auction(String itemName, String description, BigDecimal startingPrice, LocalDateTime endTime) {
        this.id = UUID.randomUUID().toString();
        this.itemName = itemName;
        this.description = description;
        this.startingPrice = startingPrice;
        this.endTime = endTime;
        this.bids = new ArrayList<>();
        this.observers = ConcurrentHashMap.newKeySet(); // Thread-safe set
        this.state = AuctionStatus.ACTIVE;
    }

    // --- Core Bidding and Auction Logic ---

    public synchronized void placeBid(User bidder, BigDecimal amount) {
        if (state != AuctionStatus.ACTIVE) {
            throw new IllegalStateException("Auction is not active.");
        }
        if (LocalDateTime.now().isAfter(endTime)) {
            endAuction();
            throw new IllegalStateException("Auction has already ended.");
        }

        Bid highestBid = getHighestBid();
        BigDecimal currentMaxAmount = (highestBid == null) ? startingPrice : highestBid.getAmount();

        if (amount.compareTo(currentMaxAmount) <= 0) {
            throw new IllegalArgumentException("Bid must be higher than the current highest bid.");
        }

        User previousHighestBidder = (highestBid != null) ? highestBid.getBidder() : null;

        Bid newBid = new Bid(bidder, amount);
        bids.add(newBid);
        addObserver(bidder); // The new bidder is now an observer

        System.out.printf("SUCCESS: %s placed a bid of $%.2f on '%s'.\n", bidder.getName(), amount, itemName);

        // Notify the previous highest bidder that they have been outbid
        if (previousHighestBidder != null && !previousHighestBidder.equals(bidder)) {
            notifyObserver(previousHighestBidder, String.format("You have been outbid on '%s'! The new highest bid is $%.2f.", itemName, amount));
        }
    }

    public synchronized void endAuction() {
        if (state != AuctionStatus.ACTIVE) {
            return; // Already ended
        }

        this.state = AuctionStatus.CLOSED;
        this.winningBid = getHighestBid();

        String endMessage;
        if (winningBid != null) {
            endMessage = String.format("Auction for '%s' has ended. Winner is %s with a bid of $%.2f!",
                    itemName, winningBid.getBidder().getName(), winningBid.getAmount());
        } else {
            endMessage = String.format("Auction for '%s' has ended. There were no bids.", itemName);
        }

        System.out.println("\n" + endMessage.toUpperCase());
        notifyAllObservers(endMessage);
    }

    public Bid getHighestBid() {
        if (bids.isEmpty()) {
            return null;
        }
        return Collections.max(bids);
    }

    public boolean isActive() {
        return state == AuctionStatus.ACTIVE;
    }

    // --- Observer Pattern Methods ---

    private void addObserver(AuctionObserver observer) {
        observers.add(observer);
    }

    private void notifyAllObservers(String message) {
        for (AuctionObserver observer : observers) {
            observer.onUpdate(this, message);
        }
    }

    private void notifyObserver(AuctionObserver observer, String message) {
        observer.onUpdate(this, message);
    }

    // --- Getters ---
    public String getId() { return id; }
    public String getItemName() { return itemName; }
    public List<Bid> getBidHistory() { return Collections.unmodifiableList(bids); }
    public AuctionStatus getState() { return state; }
    public Bid getWinningBid() { return winningBid; }
}