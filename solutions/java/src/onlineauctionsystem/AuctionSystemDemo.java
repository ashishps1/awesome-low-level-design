package onlineauctionsystem;

import java.util.Date;

public class AuctionSystemDemo {
    public static void run() {
        AuctionSystem auctionSystem = AuctionSystem.getInstance();

        // Register users
        User user1 = auctionSystem.registerUser("u1", "Alice");
        User user2 = auctionSystem.registerUser("u2", "Bob");
        User user3 = auctionSystem.registerUser("u3", "Carol");

        Item item1 = new Item("Vintage Guitar", "1960s electric guitar");
        Item item2 = new Item("Macbook air 2017", "fully working, no defects");

        // Create auctions
        Auction auction1 = auctionSystem.createAuction(user1, item1, 400, new Date(), new Date(System.currentTimeMillis() + 5000));
        Auction auction2 = auctionSystem.createAuction(user1, item2, 700.0, new Date(), new Date(System.currentTimeMillis() + 6000));

        // Place bids
        auctionSystem.placeBid(auction1.getId(), new Bid(user2, 450.0));
        auctionSystem.placeBid(auction1.getId(), new Bid(user3, 300.0));

        try {
            Thread.sleep(6000); // let auctions expire
            auctionSystem.shutdown();
        } catch (InterruptedException e) {
            System.out.println("Interrupted Exception: " + e.getMessage());
        }
    }
}
