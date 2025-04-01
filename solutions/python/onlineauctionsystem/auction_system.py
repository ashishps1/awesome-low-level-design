from user import User
from auction_listing import AuctionListing
from bid import Bid
from typing import List

class AuctionSystem:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.users = {}
            cls._instance.auction_listings = {}
        return cls._instance

    @classmethod
    def get_instance(cls):
        return cls()

    def register_user(self, user: User):
        self.users[user.id] = user

    def create_auction_listing(self, listing: AuctionListing):
        self.auction_listings[listing.id] = listing

    def search_auction_listings(self, keyword: str) -> List[AuctionListing]:
        return [listing for listing in self.auction_listings.values() if keyword.lower() in listing.item_name.lower()]

    def place_bid(self, listing_id: str, bid: Bid):
        listing = self.auction_listings.get(listing_id)
        if listing:
            listing.place_bid(bid)