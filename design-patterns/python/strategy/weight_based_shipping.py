from .shipping_strategy import ShippingStrategy


class WeightBasedShipping(ShippingStrategy):
    """Concrete Strategy - weight-based shipping"""
    
    def __init__(self, rate_per_kg: float = 2.0):
        self._rate_per_kg = rate_per_kg
    
    def calculate_cost(self, order) -> float:
        print(f"WeightBasedShipping: Calculating cost for {order}")
        return order.weight * self._rate_per_kg