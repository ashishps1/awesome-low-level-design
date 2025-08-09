from abc import ABC, abstractmethod
from auction import Auction

class AuctionObserver(ABC):
    @abstractmethod
    def on_update(self, auction: 'Auction', message: str):
        pass