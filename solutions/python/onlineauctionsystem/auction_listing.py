from enum import Enum
import threading

class AuctionStatus(Enum):
    ACTIVE = 1
    CLOSED = 2

class AuctionListing:
    def __init__(self, listing_id, item_name, description, starting_price, duration, seller):
        self.id = listing_id
        self.item_name = item_name
        self.description = description
        self.starting_price = starting_price
        self.duration = duration
        self.seller = seller
        self.status = AuctionStatus.ACTIVE
        self.current_highest_bid = starting_price
        self.current_highest_bidder = None
        self.bids = []
        self.lock = threading.Lock()

    def place_bid(self, bid):
        with self.lock:
            if self.status == AuctionStatus.ACTIVE and bid.get_amount() > self.current_highest_bid:
                self.current_highest_bid = bid.get_amount()
                self.current_highest_bidder = bid.get_bidder()
                self.bids.append(bid)
                self.notify_observers()

    def close_auction(self):
        with self.lock:
            if self.status == AuctionStatus.ACTIVE:
                self.status = AuctionStatus.CLOSED
                self.notify_observers()

    def get_id(self):
        return self.id

    def get_item_name(self):
        return self.item_name

    def get_description(self):
        return self.description

    def get_duration(self):
        return self.duration

    def notify_observers(self):
        # Notify observers (bidders) about the updated highest bid or auction closure
        # ...
        pass