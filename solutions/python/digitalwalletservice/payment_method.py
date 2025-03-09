class PaymentMethod:
    def __init__(self, id, user):
        self.id = id
        self.user = user

    def process_payment(self, amount, currency):
        raise NotImplementedError