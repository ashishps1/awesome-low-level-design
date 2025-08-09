from abc import ABC, abstractmethod
from enums import TransactionType
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class ExecutionStrategy(ABC):
    @abstractmethod
    def can_execute(self, order: 'Order', market_price: float) -> bool:
        pass

class LimitOrderStrategy(ExecutionStrategy):
    def __init__(self, transaction_type: TransactionType):
        self.type = transaction_type

    def can_execute(self, order: 'Order', market_price: float) -> bool:
        if self.type == TransactionType.BUY:
            # Buy if market price is less than or equal to limit price
            return market_price <= order.get_price()
        else:  # SELL
            # Sell if market price is greater than or equal to limit price
            return market_price >= order.get_price()

class MarketOrderStrategy(ExecutionStrategy):
    def can_execute(self, order: 'Order', market_price: float) -> bool:
        return True  # Market orders can always execute