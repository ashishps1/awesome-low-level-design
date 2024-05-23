package onlineauctionsystem;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class AuctionSystem {
    private static AuctionSystem instance;
    private final Map<String, User> users;
    private final Map<String, AuctionListing> auctionListings;

    private AuctionSystem() {
        users = new ConcurrentHashMap<>();
        auctionListings = new ConcurrentHashMap<>();
    }

    public static synchronized AuctionSystem getInstance() {
        if (instance == null) {
            instance = new AuctionSystem();
        }
        return instance;
    }

    public void registerUser(User user) {
        users.put(user.getId(), user);
    }

    public User getUser(String userId) {
        return users.get(userId);
    }

    public void createAuctionListing(AuctionListing auctionListing) {
        auctionListings.put(auctionListing.getId(), auctionListing);
        startAuctionTimer(auctionListing);
    }

    public List<AuctionListing> searchAuctionListings(String keyword) {
        List<AuctionListing> matchingListings = new ArrayList<>();
        for (AuctionListing auctionListing : auctionListings.values()) {
            if (auctionListing.getItemName().contains(keyword) || auctionListing.getDescription().contains(keyword)) {
                matchingListings.add(auctionListing);
            }
        }
        return matchingListings;
    }

    public void placeBid(String auctionListingId, Bid bid) {
        AuctionListing auctionListing = auctionListings.get(auctionListingId);
        if (auctionListing != null) {
            auctionListing.placeBid(bid);
        }
    }

    private void startAuctionTimer(AuctionListing auctionListing) {
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                auctionListing.closeAuction();
            }
        }, auctionListing.getDuration());
    }
}
