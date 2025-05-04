package onlineauctionsystem;

import java.util.Date;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.CopyOnWriteArrayList;

public class Auction {
    private final String id;
    private final Item item;
    private final Date startTime;
    private final Date endTime;
    private AuctionStatus status;
    private Bid highestBid;
    private final List<Bid> bidHistory;

    public Auction(User seller, Item item, double startingPrice, Date startTime, Date endTime) {
        this.id = UUID.randomUUID().toString();
        this.item = item;
        this.startTime = startTime;
        this.endTime = endTime;
        this.status = AuctionStatus.ACTIVE;
        this.highestBid = new Bid(seller, startingPrice);
        this.bidHistory = new CopyOnWriteArrayList<>();
    }

    public synchronized void placeBid(Bid bid) {
        if (status == AuctionStatus.CLOSED) {
            throw new IllegalStateException("Auction already ended");
        }
        if (bid.getAmount() <= highestBid.getAmount()) {
            throw new IllegalArgumentException("Bid too low");
        }

        highestBid = bid;
        bidHistory.add(bid);
        System.out.println("New highest bid: " + bid.getAmount() + " by " + bid.getBidder().getUsername());
        notifyObservers();
    }

    public synchronized void closeAuction() {
        if (status == AuctionStatus.CLOSED) return;

        status = AuctionStatus.CLOSED;
        System.out.println("Auction for " + item.getName() + " closed. Winner: " + highestBid.getBidder().getUsername() +
                " with " + highestBid.getAmount());
    }

    public boolean isActive() {
        return status == AuctionStatus.ACTIVE && new Date().before(endTime);
    }

    // Getters and setters
    public String getId() {
        return id;
    }

    public Bid getHighestBid() {
        return highestBid;
    }

    public Item getItem() {
        return item;
    }

    public AuctionStatus getStatus() {
        return status;
    }

    private void notifyObservers() {
        // Notify observers (bidders) about the updated highest bid or auction closure
        // ...
    }
}
