from payment_method import PaymentMethod

class CreditCard(PaymentMethod):
    def __init__(self, id, user, card_number, expiration_date, cvv):
        super().__init__(id, user)
        self.card_number = card_number
        self.expiration_date = expiration_date
        self.cvv = cvv

    def process_payment(self, amount, currency):
        # Process credit card payment
        return True
