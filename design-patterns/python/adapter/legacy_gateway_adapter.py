from .payment_processor import PaymentProcessor
from .legacy_gateway import LegacyGateway


class LegacyGatewayAdapter(PaymentProcessor):
    """Adapter - Adapts the LegacyGateway to the PaymentProcessor interface"""
    
    def __init__(self, legacy_gateway: LegacyGateway):
        self._legacy_gateway = legacy_gateway

    def process_payment(self, amount: float, currency: str) -> None:
        print(f"LegacyGatewayAdapter: Processing payment of {amount} {currency}")
        self._legacy_gateway.execute_transaction(amount, currency)
        print(f"LegacyGatewayAdapter: Payment processed successfully. Txn ID: {self._legacy_gateway.get_reference_number()}")

    def is_payment_successful(self) -> bool:
        return self._legacy_gateway.check_status(self._legacy_gateway.get_reference_number())

    def get_transaction_id(self) -> str:
        return str(self._legacy_gateway.get_reference_number()) 