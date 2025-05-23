import time
from .payment_processor import PaymentProcessor


class InHousePaymentProcessor(PaymentProcessor):
    """Concrete implementation of the target interface"""
    
    def __init__(self):
        self._transaction_id = None
        self._is_payment_successful = False
    
    def process_payment(self, amount: float, currency: str) -> None:
        print(f"InHousePaymentProcessor: Processing payment of {amount} {currency}")
        # Process payment logic
        self._transaction_id = f"TXN_{int(time.time() * 1000)}"
        self._is_payment_successful = True
        print(f"InHousePaymentProcessor: Payment successful. Txn ID: {self._transaction_id}")
    
    def is_payment_successful(self) -> bool:
        return self._is_payment_successful
    
    def get_transaction_id(self) -> str:
        return self._transaction_id