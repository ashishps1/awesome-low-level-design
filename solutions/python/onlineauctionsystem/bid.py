from datetime import datetime
from decimal import Decimal
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from user import User

class Bid:
    def __init__(self, bidder: 'User', amount: Decimal):
        self.bidder = bidder
        self.amount = amount
        self.timestamp = datetime.now()

    def get_bidder(self) -> 'User':
        return self.bidder

    def get_amount(self) -> Decimal:
        return self.amount

    def get_timestamp(self) -> datetime:
        return self.timestamp

    def __lt__(self, other: 'Bid') -> bool:
        if self.amount != other.amount:
            return self.amount < other.amount
        return self.timestamp > other.timestamp

    def __eq__(self, other: 'Bid') -> bool:
        return self.amount == other.amount and self.timestamp == other.timestamp

    def __le__(self, other: 'Bid') -> bool:
        return self < other or self == other

    def __gt__(self, other: 'Bid') -> bool:
        return not self <= other

    def __ge__(self, other: 'Bid') -> bool:
        return not self < other

    def __ne__(self, other: 'Bid') -> bool:
        return not self == other

    def __str__(self) -> str:
        return f"Bidder: {self.bidder.get_name()}, Amount: {self.amount:.2f}, Time: {self.timestamp}"