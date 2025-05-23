from .shipping_strategy import ShippingStrategy


class DistanceBasedShipping(ShippingStrategy):
    """Concrete Strategy - distance-based shipping"""
    
    def __init__(self, rate_per_km: float = 0.5):
        self._rate_per_km = rate_per_km
    
    def calculate_cost(self, order) -> float:
        print(f"DistanceBasedShipping: Calculating cost for {order}")
        return order.distance * self._rate_per_km