from .order import Order
from .shipping_cost_service import ShippingCostService
from .flat_rate_shipping import FlatRateShipping
from .weight_based_shipping import WeightBasedShipping
from .distance_based_shipping import DistanceBasedShipping
from .third_party_api_shipping import ThirdPartyApiShipping
from .shipping_cost_calculator_naive import ShippingCostCalculatorNaive


def ecommerce_app_v2_demo():
    """Demonstrate Strategy pattern with e-commerce shipping"""
    print("=== Strategy Pattern Demo - E-commerce App V2 ===")
    
    # Create order
    order = Order(weight=2.5, distance=150.0, value=99.99)
    print(f"Order details: {order}")
    
    # Create service with initial strategy
    shipping_service = ShippingCostService(FlatRateShipping())
    
    print(f"\n--- Flat Rate Shipping ---")
    cost = shipping_service.calculate_shipping_cost(order)
    print(f"Shipping cost: ${cost:.2f}")
    
    print(f"\n--- Weight Based Shipping ---")
    shipping_service.set_strategy(WeightBasedShipping())
    cost = shipping_service.calculate_shipping_cost(order)
    print(f"Shipping cost: ${cost:.2f}")
    
    print(f"\n--- Distance Based Shipping ---")
    shipping_service.set_strategy(DistanceBasedShipping())
    cost = shipping_service.calculate_shipping_cost(order)
    print(f"Shipping cost: ${cost:.2f}")
    
    print(f"\n--- Third Party API Shipping ---")
    shipping_service.set_strategy(ThirdPartyApiShipping())
    cost = shipping_service.calculate_shipping_cost(order)
    print(f"Shipping cost: ${cost:.2f}")


def ecommerce_app_v1_demo():
    """Demonstrate naive implementation (anti-pattern)"""
    print("\n=== Naive Implementation Demo - E-commerce App V1 ===")
    
    order = Order(weight=2.5, distance=150.0, value=99.99)
    calculator = ShippingCostCalculatorNaive()
    
    print(f"Order details: {order}")
    
    cost1 = calculator.calculate_shipping_cost(order, "FLAT_RATE")
    print(f"Flat rate cost: ${cost1:.2f}")
    
    cost2 = calculator.calculate_shipping_cost(order, "WEIGHT_BASED")
    print(f"Weight-based cost: ${cost2:.2f}")
    
    cost3 = calculator.calculate_shipping_cost(order, "DISTANCE_BASED")
    print(f"Distance-based cost: ${cost3:.2f}")


if __name__ == "__main__":
    ecommerce_app_v2_demo()
    ecommerce_app_v1_demo()