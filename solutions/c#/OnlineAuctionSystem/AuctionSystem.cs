using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace OnlineAuctionSystem
{
    public class AuctionSystem
    {
        private static AuctionSystem _instance;
        private readonly ConcurrentDictionary<string, User> _users;
        private readonly ConcurrentDictionary<string, AuctionListing> _auctionListings;

        private AuctionSystem()
        {
            _users = new ConcurrentDictionary<string, User>();
            _auctionListings = new ConcurrentDictionary<string, AuctionListing>();
        }

        public static AuctionSystem GetInstance()
        {
            if (_instance == null)
            {
                _instance = new AuctionSystem();
            }
            return _instance;
        }

        public void RegisterUser(User user)
        {
            _users[user.Id] = user;
        }

        public User GetUser(string userId)
        {
            return _users.ContainsKey(userId) ? _users[userId] : null;
        }

        public void CreateAuctionListing(AuctionListing auctionListing)
        {
            _auctionListings[auctionListing.Id] = auctionListing;
            StartAuctionTimer(auctionListing);
        }

        public List<AuctionListing> SearchAuctionListings(string keyword)
        {
            return _auctionListings.Values
                .Where(listing => listing.ItemName.Contains(keyword) || listing.Description.Contains(keyword))
                .ToList();
        }

        public void PlaceBid(string auctionListingId, Bid bid)
        {
            if (_auctionListings.TryGetValue(auctionListingId, out var auctionListing))
            {
                auctionListing.PlaceBid(bid);
            }
        }

        private void StartAuctionTimer(AuctionListing auctionListing)
        {
            var timer = new Timer(state =>
            {
                auctionListing.CloseAuction();
            }, null, TimeSpan.FromMilliseconds(auctionListing.Duration), Timeout.InfiniteTimeSpan);
        }
    }
}