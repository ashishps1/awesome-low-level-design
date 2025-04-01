using System.Collections.Concurrent;
using System.Collections.Generic;

namespace OnlineAuctionSystem
{
    public class AuctionListing
    {
        public string Id { get; }
        public string ItemName { get; }
        public string Description { get; }
        public double StartingPrice { get; }
        public long Duration { get; }
        public User Seller { get; }
        public AuctionStatus Status { get; private set; }
        public double CurrentHighestBid { get; private set; }
        public User CurrentHighestBidder { get; private set; }
        private readonly List<Bid> _bids;

        public AuctionListing(string id, string itemName, string description, double startingPrice, long duration, User seller)
        {
            Id = id;
            ItemName = itemName;
            Description = description;
            StartingPrice = startingPrice;
            Duration = duration;
            Seller = seller;
            Status = AuctionStatus.ACTIVE;
            CurrentHighestBid = startingPrice;
            CurrentHighestBidder = null;
            _bids = new List<Bid>();
        }

        public void PlaceBid(Bid bid)
        {
            lock (this)
            {
                if (Status == AuctionStatus.ACTIVE && bid.Amount > CurrentHighestBid)
                {
                    CurrentHighestBid = bid.Amount;
                    CurrentHighestBidder = bid.Bidder;
                    _bids.Add(bid);
                    NotifyObservers();
                }
            }
        }

        public void CloseAuction()
        {
            lock (this)
            {
                if (Status == AuctionStatus.ACTIVE)
                {
                    Status = AuctionStatus.CLOSED;
                    NotifyObservers();
                }
            }
        }

        private void NotifyObservers()
        {
            // Notify observers (bidders) about the updated highest bid or auction closure
            // ...
        }
    }
}