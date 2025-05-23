from .order import Order


class ShippingCostCalculatorNaive:
    """Naive implementation without strategy pattern (anti-pattern)"""
    
    def calculate_shipping_cost(self, order: Order, shipping_type: str) -> float:
        if shipping_type == "FLAT_RATE":
            print(f"Calculating flat rate shipping for {order}")
            return 10.0
        elif shipping_type == "WEIGHT_BASED":
            print(f"Calculating weight-based shipping for {order}")
            return order.weight * 2.0
        elif shipping_type == "DISTANCE_BASED":
            print(f"Calculating distance-based shipping for {order}")
            return order.distance * 0.5
        elif shipping_type == "THIRD_PARTY":
            print(f"Calculating third-party shipping for {order}")
            return 15.0  # Simplified
        else:
            raise ValueError(f"Unknown shipping type: {shipping_type}")