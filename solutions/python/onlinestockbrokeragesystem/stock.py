from typing import List
from stock_observer import StockObserver

class Stock:
    def __init__(self, symbol: str, initial_price: float):
        self.symbol = symbol
        self.price = initial_price
        self.observers: List[StockObserver] = []

    def get_symbol(self) -> str:
        return self.symbol

    def get_price(self) -> float:
        return self.price

    def set_price(self, new_price: float) -> None:
        if self.price != new_price:
            self.price = new_price
            self._notify_observers()

    def add_observer(self, observer: StockObserver) -> None:
        self.observers.append(observer)

    def remove_observer(self, observer: StockObserver) -> None:
        if observer in self.observers:
            self.observers.remove(observer)

    def _notify_observers(self) -> None:
        for observer in self.observers:
            observer.update(self)