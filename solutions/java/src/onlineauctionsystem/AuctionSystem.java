package onlineauctionsystem;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class AuctionSystem {
    private static AuctionSystem instance;
    private final Map<String, User> users;
    private final Map<String, Auction> auctions;
    private final ScheduledExecutorService scheduler;

    private AuctionSystem() {
        users = new ConcurrentHashMap<>();
        auctions = new ConcurrentHashMap<>();
        this.scheduler = Executors.newScheduledThreadPool(1);
    }

    public static synchronized AuctionSystem getInstance() {
        if (instance == null) {
            instance = new AuctionSystem();
        }
        return instance;
    }

    public User registerUser(String username, String name) {
        User user = new User(username, name);
        users.put(username, user);
        return user;
    }

    public User getUser(String userId) {
        return users.get(userId);
    }

    public Auction createAuction(User seller, Item item, double startingPrice, Date start, Date end) {
        Auction auction = new Auction(seller, item, startingPrice, start, end);
        auctions.put(auction.getId(), auction);

        long delay = end.getTime() - new Date().getTime();
        scheduler.schedule(auction::closeAuction, delay, TimeUnit.MILLISECONDS);

        System.out.println("Auction created: " + auction.getId());
        return auction;
    }

    public void placeBid(String auctionId, Bid bid) {
        Auction auction = auctions.get(auctionId);
        if (auction == null) throw new IllegalArgumentException("Invalid auction ID");
        auction.placeBid(bid);
    }

    public List<Auction> viewActiveAuctions() {
        return auctions.values().stream().filter(Auction::isActive).toList();
    }

    public void shutdown() {
        scheduler.shutdown();
    }
}
