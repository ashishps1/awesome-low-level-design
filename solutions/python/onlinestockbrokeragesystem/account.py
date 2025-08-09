import threading
from typing import Dict
from exceptions import InsufficientFundsException, InsufficientStockException

class Account:
    def __init__(self, initial_cash: float):
        self.balance = initial_cash
        self.portfolio: Dict[str, int] = {}  # Stock symbol -> quantity
        self.lock = threading.Lock()

    def debit(self, amount: float) -> None:
        with self.lock:
            if self.balance < amount:
                raise InsufficientFundsException(f"Insufficient funds to debit {amount}")
            self.balance -= amount

    def credit(self, amount: float) -> None:
        with self.lock:
            self.balance += amount

    def add_stock(self, symbol: str, quantity: int) -> None:
        with self.lock:
            self.portfolio[symbol] = self.portfolio.get(symbol, 0) + quantity

    def remove_stock(self, symbol: str, quantity: int) -> None:
        with self.lock:
            current_quantity = self.portfolio.get(symbol, 0)
            if current_quantity < quantity:
                raise InsufficientStockException(f"Not enough {symbol} stock to sell.")
            self.portfolio[symbol] = current_quantity - quantity

    def get_balance(self) -> float:
        return self.balance

    def get_portfolio(self) -> Dict[str, int]:
        return self.portfolio.copy()

    def get_stock_quantity(self, symbol: str) -> int:
        return self.portfolio.get(symbol, 0)