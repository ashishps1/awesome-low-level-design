from .shipping_strategy import ShippingStrategy


class FlatRateShipping(ShippingStrategy):
    """Concrete Strategy - flat rate shipping"""
    
    def __init__(self, rate: float = 10.0):
        self._rate = rate
    
    def calculate_cost(self, order) -> float:
        print(f"FlatRateShipping: Calculating cost for {order}")
        return self._rate