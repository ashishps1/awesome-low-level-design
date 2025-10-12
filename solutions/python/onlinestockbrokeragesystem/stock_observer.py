from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from stock import Stock

class StockObserver(ABC):
    @abstractmethod
    def update(self, stock: 'Stock') -> None:
        pass