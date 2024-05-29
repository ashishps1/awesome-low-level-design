from payment import Payment

class CreditCardPayment(Payment):
    def process_payment(self, amount: float) -> bool:
        # Process credit card payment
        return True
