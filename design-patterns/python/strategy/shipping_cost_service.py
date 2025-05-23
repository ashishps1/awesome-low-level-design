from .shipping_strategy import ShippingStrategy
from .order import Order


class ShippingCostService:
    """Context class that uses a shipping strategy"""
    
    def __init__(self, strategy: ShippingStrategy):
        self._strategy = strategy
    
    def set_strategy(self, strategy: ShippingStrategy) -> None:
        """Runtime strategy switching"""
        self._strategy = strategy
    
    def calculate_shipping_cost(self, order: Order) -> float:
        """Delegate to the current strategy"""
        return self._strategy.calculate_cost(order)