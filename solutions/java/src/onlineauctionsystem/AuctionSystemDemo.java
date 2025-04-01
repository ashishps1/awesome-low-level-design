package onlineauctionsystem;

import java.util.List;

public class AuctionSystemDemo {
    public static void run() {
        AuctionSystem auctionSystem = AuctionSystem.getInstance();

        // Register users
        User user1 = new User("1", "John Doe", "john@example.com");
        User user2 = new User("2", "Jane Smith", "jane@example.com");
        auctionSystem.registerUser(user1);
        auctionSystem.registerUser(user2);

        // Create auction listings
        AuctionListing listing1 = new AuctionListing("1", "Item 1", "Description 1", 100.0, 60000, user1);
        AuctionListing listing2 = new AuctionListing("2", "Item 2", "Description 2", 50.0, 120000, user2);
        auctionSystem.createAuctionListing(listing1);
        auctionSystem.createAuctionListing(listing2);

        // Search auction listings
        List<AuctionListing> searchResults = auctionSystem.searchAuctionListings("Item");
        System.out.println("Search Results:");
        for (AuctionListing listing : searchResults) {
            System.out.println(listing.getItemName());
        }

        // Place bids
        Bid bid1 = new Bid("1", user2, 150.0);
        Bid bid2 = new Bid("2", user1, 200.0);
        auctionSystem.placeBid(listing1.getId(), bid1);
        auctionSystem.placeBid(listing1.getId(), bid2);
    }
}
