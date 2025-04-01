from payment import Payment

class CashPayment(Payment):
    def process_payment(self, amount: float) -> bool:
        # Process cash payment
        return True
