from .in_house_payment_processor import InHousePaymentProcessor
from .legacy_gateway import LegacyGateway
from .legacy_gateway_adapter import LegacyGatewayAdapter
from .checkout_service import CheckoutService


def ecommerce_app_v1():
    """Demo using in-house payment processor only"""
    processor = InHousePaymentProcessor()
    checkout = CheckoutService(processor)
    checkout.checkout(199.99, "USD")


def ecommerce_app_v2():
    """Demo using both in-house and legacy payment processors"""
    in_house_processor = InHousePaymentProcessor()
    legacy_processor = LegacyGatewayAdapter(LegacyGateway())

    checkout_service = CheckoutService(in_house_processor)
    checkout_service.checkout(100, "USD")

    print("--------------------------------")

    checkout_service = CheckoutService(legacy_processor)
    checkout_service.checkout(100, "USD")


if __name__ == "__main__":
    print("=== ECommerce App V1 ===")
    ecommerce_app_v1()
    
    print("\n=== ECommerce App V2 ===")
    ecommerce_app_v2() 