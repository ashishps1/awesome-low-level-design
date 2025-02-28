using System;
using System.Collections.Generic;

namespace OnlineAuctionSystem
{
    public class AuctionSystemDemo
    {
        public static void Run()
        {
            var auctionSystem = AuctionSystem.GetInstance();

            // Register users
            var user1 = new User("1", "John Doe", "john@example.com");
            var user2 = new User("2", "Jane Smith", "jane@example.com");
            auctionSystem.RegisterUser(user1);
            auctionSystem.RegisterUser(user2);

            // Create auction listings
            var listing1 = new AuctionListing("1", "Item 1", "Description 1", 100.0, 60000, user1);
            var listing2 = new AuctionListing("2", "Item 2", "Description 2", 50.0, 120000, user2);
            auctionSystem.CreateAuctionListing(listing1);
            auctionSystem.CreateAuctionListing(listing2);

            // Search auction listings
            List<AuctionListing> searchResults = auctionSystem.SearchAuctionListings("Item");
            Console.WriteLine("Search Results:");
            foreach (var listing in searchResults)
            {
                Console.WriteLine(listing.ItemName);
            }

            // Place bids
            var bid1 = new Bid("1", user2, 150.0);
            var bid2 = new Bid("2", user1, 200.0);
            auctionSystem.PlaceBid(listing1.Id, bid1);
            auctionSystem.PlaceBid(listing1.Id, bid2);
        }
    }
}