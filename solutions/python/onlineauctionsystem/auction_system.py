import threading

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
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

    def register_user(self, user):
        self.users[user.get_id()] = user

    def get_user(self, user_id):
        return self.users.get(user_id)

    def create_auction_listing(self, auction_listing):
        self.auction_listings[auction_listing.get_id()] = auction_listing
        self.start_auction_timer(auction_listing)

    def search_auction_listings(self, keyword):
        matching_listings = []
        for auction_listing in self.auction_listings.values():
            if keyword in auction_listing.get_item_name() or keyword in auction_listing.get_description():
                matching_listings.append(auction_listing)
        return matching_listings

    def place_bid(self, auction_listing_id, bid):
        auction_listing = self.auction_listings.get(auction_listing_id)
        if auction_listing:
            auction_listing.place_bid(bid)

    def start_auction_timer(self, auction_listing):
        timer = threading.Timer(auction_listing.get_duration() / 1000, auction_listing.close_auction)
        timer.start()