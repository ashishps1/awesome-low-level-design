import uuid
from account import Account
from stock import Stock
from stock_observer import StockObserver
from order import Order

class User(StockObserver):
    def __init__(self, name: str, initial_cash: float):
        self.user_id = str(uuid.uuid4())
        self.name = name
        self.account = Account(initial_cash)

    def get_user_id(self) -> str:
        return self.user_id

    def get_name(self) -> str:
        return self.name

    def get_account(self) -> Account:
        return self.account

    def update(self, stock: Stock) -> None:
        print(f"[Notification for {self.name}] Stock {stock.get_symbol()} price updated to: ${stock.get_price():.2f}")

    def order_status_update(self, order: 'Order') -> None:
        print(f"[Order Notification for {self.name}] Order {order.get_order_id()} for {order.get_stock().get_symbol()} is now {order.get_status().value}.")
