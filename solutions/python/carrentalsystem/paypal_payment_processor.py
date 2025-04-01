from payment_processor import PaymentProcessor

class PayPalPaymentProcessor(PaymentProcessor):
    def process_payment(self, amount):
        # Process PayPal payment
        # ...
        return True
