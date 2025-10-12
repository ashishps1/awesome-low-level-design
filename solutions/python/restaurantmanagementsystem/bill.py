from abc import ABC, abstractmethod
from typing import TYPE_CHECKING
from order import Order

# Decorator Pattern for Bills
class BillComponent(ABC):
    @abstractmethod
    def calculate_total(self) -> float:
        pass
    
    @abstractmethod
    def get_description(self) -> str:
        pass

class Bill:
    def __init__(self, component: BillComponent):
        self._component = component
    
    def print_bill(self):
        print("\n--- BILL ---")
        print(f"Description: {self._component.get_description()}")
        print(f"Total: ${self._component.calculate_total():.2f}")
        print("------------")

class BaseBill(BillComponent):
    def __init__(self, order: Order):
        self._order = order
    
    def calculate_total(self) -> float:
        return self._order.get_total_price()
    
    def get_description(self) -> str:
        return "Order Items"