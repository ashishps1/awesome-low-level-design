using System;

namespace OnlineAuctionSystem
{
    public class Bid
    {
        public string Id { get; }
        public User Bidder { get; }
        public double Amount { get; }
        public DateTime Timestamp { get; }

        public Bid(string id, User bidder, double amount)
        {
            Id = id;
            Bidder = bidder;
            Amount = amount;
            Timestamp = DateTime.Now;
        }
    }
}