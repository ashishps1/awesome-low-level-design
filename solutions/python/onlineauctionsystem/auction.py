from typing import List, Set, Optional
from bid import Bid
from auction_state import AuctionState
from datetime import datetime
from decimal import Decimal
import uuid
import threading
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from user import User
    from auction_observer import AuctionObserver

class Auction:
    def __init__(self, item_name: str, description: str, starting_price: Decimal, end_time: datetime):
        self.id = str(uuid.uuid4())
        self.item_name = item_name
        self.description = description
        self.starting_price = starting_price
        self.end_time = end_time
        self.bids: List[Bid] = []
        self.observers: Set[AuctionObserver] = set()
        self.state = AuctionState.ACTIVE
        self.winning_bid: Optional[Bid] = None
        self._lock = threading.RLock()

    def place_bid(self, bidder: 'User', amount: Decimal):
        with self._lock:
            if self.state != AuctionState.ACTIVE:
                raise Exception("Auction is not active.")
            if datetime.now() > self.end_time:
                self.end_auction()
                raise Exception("Auction has already ended.")

            highest_bid = self.get_highest_bid()
            current_max_amount = self.starting_price if highest_bid is None else highest_bid.get_amount()

            if amount <= current_max_amount:
                raise ValueError("Bid must be higher than the current highest bid.")

            previous_highest_bidder = highest_bid.get_bidder() if highest_bid is not None else None

            new_bid = Bid(bidder, amount)
            self.bids.append(new_bid)
            self.add_observer(bidder)

            print(f"SUCCESS: {bidder.get_name()} placed a bid of ${amount:.2f} on '{self.item_name}'.")

            if previous_highest_bidder is not None and previous_highest_bidder != bidder:
                self.notify_observer(previous_highest_bidder, 
                    f"You have been outbid on '{self.item_name}'! The new highest bid is ${amount:.2f}.")

    def end_auction(self):
        with self._lock:
            if self.state != AuctionState.ACTIVE:
                return

            self.state = AuctionState.CLOSED
            self.winning_bid = self.get_highest_bid()

            if self.winning_bid is not None:
                end_message = f"Auction for '{self.item_name}' has ended. Winner is {self.winning_bid.get_bidder().get_name()} with a bid of ${self.winning_bid.get_amount():.2f}!"
            else:
                end_message = f"Auction for '{self.item_name}' has ended. There were no bids."

            print(f"\n{end_message.upper()}")
            self.notify_all_observers(end_message)

    def get_highest_bid(self) -> Optional[Bid]:
        if not self.bids:
            return None
        return max(self.bids)

    def is_active(self) -> bool:
        return self.state == AuctionState.ACTIVE

    def add_observer(self, observer: 'AuctionObserver'):
        self.observers.add(observer)

    def notify_all_observers(self, message: str):
        for observer in self.observers:
            observer.on_update(self, message)

    def notify_observer(self, observer: 'AuctionObserver', message: str):
        observer.on_update(self, message)

    def get_id(self) -> str:
        return self.id

    def get_item_name(self) -> str:
        return self.item_name

    def get_bid_history(self) -> List[Bid]:
        return self.bids.copy()

    def get_state(self) -> AuctionState:
        return self.state

    def get_winning_bid(self) -> Optional[Bid]:
        return self.winning_bid