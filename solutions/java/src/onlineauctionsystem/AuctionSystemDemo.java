package onlineauctionsystem;

import onlineauctionsystem.entities.Auction;
import onlineauctionsystem.entities.User;

import java.math.BigDecimal;
import java.time.LocalDateTime;

public class AuctionSystemDemo {
    public static void main(String[] args) {
        AuctionService auctionService = AuctionService.getInstance();

        // Create users
        User alice = auctionService.createUser("Alice");
        User bob = auctionService.createUser("Bob");
        User carol = auctionService.createUser("Carol");

        System.out.println("=============================================");
        System.out.println("        Online Auction System Demo           ");
        System.out.println("=============================================");

        // 2. Create an auction that will last for a short duration
        LocalDateTime endTime = LocalDateTime.now().plusSeconds(10);
        Auction laptopAuction = auctionService.createAuction(
                "Vintage Laptop",
                "A rare 1990s laptop, in working condition.",
                new BigDecimal("100.00"),
                endTime
        );
        System.out.println();

        // 3. Bidding war starts
        try {
            auctionService.placeBid(laptopAuction.getId(), alice.getId(), new BigDecimal("110.00"));
            Thread.sleep(500); // Simulate time passing

            auctionService.placeBid(laptopAuction.getId(), bob.getId(), new BigDecimal("120.00")); // Alice gets an outbid notification
            Thread.sleep(500);

            auctionService.placeBid(laptopAuction.getId(), carol.getId(), new BigDecimal("125.00")); // Bob gets an outbid notification
            Thread.sleep(500);                                                               // (Charlie's bid is earlier for the same amount, making him the highest bidder)

            auctionService.placeBid(laptopAuction.getId(), alice.getId(), new BigDecimal("150.00")); // Charlie gets an outbid notification

            // 4. Wait for the auction to end automatically via the scheduler
            System.out.println("\n--- Waiting for auction to end automatically... ---");
            Thread.sleep(2 * 1000); // Wait longer than the auction duration
        } catch (Exception e) {
            System.err.println("An error occurred during bidding: " + e.getMessage());
        }

        // 5. Post-auction actions
        System.out.println("\n--- Post-Auction Information ---");
        Auction endedAuction = auctionService.getAuction(laptopAuction.getId());

        // Display winner
        if (endedAuction.getWinningBid() != null) {
            System.out.printf("Final Winner: %s\n", endedAuction.getWinningBid().getBidder().getName());
            System.out.printf("Winning Price: $%.2f\n", endedAuction.getWinningBid().getAmount());
        } else {
            System.out.println("The auction ended with no winner.");
        }

        // Display bid history
        System.out.println("\nFull Bid History:");
        endedAuction.getBidHistory().forEach(System.out::println);

        // 6. Try to bid on an ended auction
        System.out.println("\n--- Attempting to bid on an ended auction ---");
        try {
            auctionService.placeBid(laptopAuction.getId(), bob.getId(), new BigDecimal("200.00"));
        } catch (IllegalStateException e) {
            System.out.println("CAUGHT EXPECTED ERROR: " + e.getMessage());
        }

        // 7. Shutdown the scheduler
        auctionService.shutdown();
    }
}
