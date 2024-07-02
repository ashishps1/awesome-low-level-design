from payment_method import PaymentMethod

class BankAccount(PaymentMethod):
    def __init__(self, id, user, account_number, routing_number):
        super().__init__(id, user)
        self.account_number = account_number
        self.routing_number = routing_number

    def process_payment(self, amount, currency):
        # Process bank account payment
        return True