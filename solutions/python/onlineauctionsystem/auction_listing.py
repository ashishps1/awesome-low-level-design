from enum import Enum
import threading
from bid import Bid
from user import User
from typing import List, Optional

class AuctionStatus(Enum):
    ACTIVE = 1
    CLOSED = 2

class AuctionListing:
    def __init__(self, id: str, item_name: str, description: str, starting_price: float, duration: int, seller: User):
        self.id = id
        self.item_name = item_name
        self.description = description
        self.starting_price = starting_price
        self.duration = duration
        self.seller = seller
        self.status = AuctionStatus.ACTIVE
        self.current_highest_bid = starting_price
        self.current_highest_bidder: Optional[User] = None
        self.bids: List[Bid] = []
        self.lock = threading.Lock()

    def place_bid(self, bid: Bid):
        with self.lock:
            if self.status == AuctionStatus.ACTIVE and bid.amount > self.current_highest_bid:
                self.current_highest_bid = bid.amount
                self.current_highest_bidder = bid.bidder
                self.bids.append(bid)
                self.notify_observers()

    def close_auction(self):
        with self.lock:
            if self.status == AuctionStatus.ACTIVE:
                self.status = AuctionStatus.CLOSED
                self.notify_observers()

    def notify_observers(self):
        # Notify observers (bidders) about the updated highest bid or auction closure
        pass