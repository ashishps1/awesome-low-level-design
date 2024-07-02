from auction_system import AuctionSystem
from auction_listing import AuctionListing
from user import User
from bid import Bid

class AuctionSystemDemo:
    @staticmethod
    def run():
        auction_system = AuctionSystem.get_instance()

        # Register users
        user1 = User("1", "John Doe", "john@example.com")
        user2 = User("2", "Jane Smith", "jane@example.com")
        auction_system.register_user(user1)
        auction_system.register_user(user2)

        # Create auction listings
        listing1 = AuctionListing("1", "Item 1", "Description 1", 100.0, 60000, user1)
        listing2 = AuctionListing("2", "Item 2", "Description 2", 50.0, 120000, user2)
        auction_system.create_auction_listing(listing1)
        auction_system.create_auction_listing(listing2)

        # Search auction listings
        search_results = auction_system.search_auction_listings("Item")
        print("Search Results:")
        for listing in search_results:
            print(listing.item_name)

        # Place bids
        bid1 = Bid("1", user2, 150.0)
        bid2 = Bid("2", user1, 200.0)
        auction_system.place_bid(listing1.id, bid1)
        auction_system.place_bid(listing1.id, bid2)

if __name__ == "__main__":
    AuctionSystemDemo.run()