from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order_item import OrderItem

class OrderObserver(ABC):
    @abstractmethod
    def update(self, item: 'OrderItem'):
        pass