from typing import Dict, Optional
from user import User
from stock import Stock
from order import Order
from order_command import BuyStockCommand, SellStockCommand
import threading

class StockBrokerageSystem:
    _instance: Optional['StockBrokerageSystem'] = None
    _lock = threading.Lock()

    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self):
        if hasattr(self, 'initialized'):
            return
        self.users: Dict[str, User] = {}
        self.stocks: Dict[str, Stock] = {}
        self.initialized = True

    @classmethod
    def get_instance(cls) -> 'StockBrokerageSystem':
        return cls()

    def register_user(self, name: str, initial_amount: float) -> User:
        user = User(name, initial_amount)
        self.users[user.get_user_id()] = user
        return user

    def add_stock(self, symbol: str, initial_price: float) -> Stock:
        stock = Stock(symbol, initial_price)
        self.stocks[stock.get_symbol()] = stock
        return stock

    def place_buy_order(self, order: Order) -> None:
        user = order.get_user()
        command = BuyStockCommand(user.get_account(), order)
        command.execute()

    def place_sell_order(self, order: Order) -> None:
        user = order.get_user()
        command = SellStockCommand(user.get_account(), order)
        command.execute()

    def cancel_order(self, order: Order) -> None:
        order.cancel()