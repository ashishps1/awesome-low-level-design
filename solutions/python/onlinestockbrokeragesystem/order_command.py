from abc import ABC, abstractmethod
from account import Account
from order import Order
from enums import OrderType
from exceptions import InsufficientFundsException, InsufficientStockException
from stock_exchange import StockExchange

class OrderCommand(ABC):
    @abstractmethod
    def execute(self) -> None:
        pass

class BuyStockCommand(OrderCommand):
    def __init__(self, account: Account, order: Order):
        self.account = account
        self.order = order
        self.stock_exchange = StockExchange.get_instance()

    def execute(self) -> None:
        # For market order, we can't pre-check funds perfectly.
        # For limit order, we can pre-authorize the amount.
        estimated_cost = self.order.get_quantity() * self.order.get_price()
        if self.order.get_type() == OrderType.LIMIT and self.account.get_balance() < estimated_cost:
            raise InsufficientFundsException("Not enough cash to place limit buy order.")
        print(f"Placing BUY order {self.order.get_order_id()} for {self.order.get_quantity()} shares of {self.order.get_stock().get_symbol()}.")
        self.stock_exchange.place_buy_order(self.order)

class SellStockCommand(OrderCommand):
    def __init__(self, account: Account, order: Order):
        self.account = account
        self.order = order
        self.stock_exchange = StockExchange.get_instance()

    def execute(self) -> None:
        if self.account.get_stock_quantity(self.order.get_stock().get_symbol()) < self.order.get_quantity():
            raise InsufficientStockException("Not enough stock to place sell order.")
        print(f"Placing SELL order {self.order.get_order_id()} for {self.order.get_quantity()} shares of {self.order.get_stock().get_symbol()}.")
        self.stock_exchange.place_sell_order(self.order)