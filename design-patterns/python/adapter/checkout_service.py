from .payment_processor import PaymentProcessor


class CheckoutService:
    """Client - Uses the PaymentProcessor interface"""
    
    def __init__(self, payment_processor: PaymentProcessor):
        self._payment_processor = payment_processor

    def checkout(self, amount: float, currency: str) -> None:
        print(f"CheckoutService: Attempting to process order for ${amount} {currency}")
        self._payment_processor.process_payment(amount, currency)
        if self._payment_processor.is_payment_successful():
            print(f"CheckoutService: Order successful! Transaction ID: {self._payment_processor.get_transaction_id()}")
        else:
            print("CheckoutService: Order failed. Payment was not successful.") 