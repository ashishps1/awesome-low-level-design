from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class OrderObserver(ABC):
    @abstractmethod
    def on_update(self, order: 'Order'):
        pass