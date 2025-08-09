from enums import OrderType, TransactionType
from user import User
from stock import Stock
from order import Order
from execution_strategy import MarketOrderStrategy, LimitOrderStrategy
from typing import Optional
import uuid

class OrderBuilder:
    def __init__(self):
        self.user: Optional[User] = None
        self.stock: Optional[Stock] = None
        self.type: Optional[OrderType] = None
        self.transaction_type: Optional[TransactionType] = None
        self.quantity: int = 0
        self.price: float = 0.0

    def for_user(self, user: User) -> 'OrderBuilder':
        self.user = user
        return self

    def with_stock(self, stock: Stock) -> 'OrderBuilder':
        self.stock = stock
        return self

    def buy(self, quantity: int) -> 'OrderBuilder':
        self.transaction_type = TransactionType.BUY
        self.quantity = quantity
        return self

    def sell(self, quantity: int) -> 'OrderBuilder':
        self.transaction_type = TransactionType.SELL
        self.quantity = quantity
        return self

    def at_market_price(self) -> 'OrderBuilder':
        self.type = OrderType.MARKET
        self.price = 0  # Not needed for market order
        return self

    def with_limit(self, limit_price: float) -> 'OrderBuilder':
        self.type = OrderType.LIMIT
        self.price = limit_price
        return self

    def build(self) -> Order:
        execution_strategy = MarketOrderStrategy() if self.type == OrderType.MARKET else LimitOrderStrategy(self.transaction_type)
        return Order(
            str(uuid.uuid4()),
            self.user,
            self.stock,
            self.type,
            self.quantity,
            self.price,
            execution_strategy,
            self.user
        )