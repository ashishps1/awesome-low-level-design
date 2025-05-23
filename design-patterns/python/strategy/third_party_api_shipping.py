from .shipping_strategy import ShippingStrategy
import random


class ThirdPartyApiShipping(ShippingStrategy):
    """Concrete Strategy - third-party API shipping"""
    
    def calculate_cost(self, order) -> float:
        print(f"ThirdPartyApiShipping: Calling external API for {order}")
        # Simulate API call with random cost
        api_cost = round(random.uniform(5.0, 25.0), 2)
        print(f"ThirdPartyApiShipping: API returned cost: ${api_cost}")
        return api_cost