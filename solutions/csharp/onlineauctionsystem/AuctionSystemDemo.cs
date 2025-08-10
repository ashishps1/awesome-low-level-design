using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

public class AuctionSystemDemo
{
    public static void Main(string[] args)
    {
        AuctionService auctionService = AuctionService.GetInstance();

        User alice = auctionService.CreateUser("Alice");
        User bob = auctionService.CreateUser("Bob");
        User carol = auctionService.CreateUser("Carol");

        Console.WriteLine("=============================================");
        Console.WriteLine("        Online Auction System Demo           ");
        Console.WriteLine("=============================================");

        DateTime endTime = DateTime.Now.AddSeconds(10);
        Auction laptopAuction = auctionService.CreateAuction(
            "Vintage Laptop",
            "A rare 1990s laptop, in working condition.",
            100.00m,
            endTime
        );
        Console.WriteLine();

        try
        {
            auctionService.PlaceBid(laptopAuction.GetId(), alice.GetId(), 110.00m);
            Thread.Sleep(500);

            auctionService.PlaceBid(laptopAuction.GetId(), bob.GetId(), 120.00m);
            Thread.Sleep(500);

            auctionService.PlaceBid(laptopAuction.GetId(), carol.GetId(), 125.00m);
            Thread.Sleep(500);

            auctionService.PlaceBid(laptopAuction.GetId(), alice.GetId(), 150.00m);

            Console.WriteLine("\n--- Waiting for auction to end automatically... ---");
            Thread.Sleep(2000);
        }
        catch (Exception e)
        {
            Console.WriteLine($"An error occurred during bidding: {e.Message}");
        }

        Console.WriteLine("\n--- Post-Auction Information ---");
        Auction endedAuction = auctionService.GetAuction(laptopAuction.GetId());

        if (endedAuction.GetWinningBid() != null)
        {
            Console.WriteLine($"Final Winner: {endedAuction.GetWinningBid().GetBidder().GetName()}");
            Console.WriteLine($"Winning Price: ${endedAuction.GetWinningBid().GetAmount():F2}");
        }
        else
        {
            Console.WriteLine("The auction ended with no winner.");
        }

        Console.WriteLine("\nFull Bid History:");
        foreach (Bid bid in endedAuction.GetBidHistory())
        {
            Console.WriteLine(bid.ToString());
        }

        Console.WriteLine("\n--- Attempting to bid on an ended auction ---");
        try
        {
            auctionService.PlaceBid(laptopAuction.GetId(), bob.GetId(), 200.00m);
        }
        catch (Exception e)
        {
            Console.WriteLine($"CAUGHT EXPECTED ERROR: {e.Message}");
        }

        auctionService.Shutdown();
    }
}