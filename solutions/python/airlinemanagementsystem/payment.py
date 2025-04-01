from enum import Enum

class PaymentStatus(Enum):
    PENDING = 1
    COMPLETED = 2
    FAILED = 3
    REFUNDED = 4

class Payment:
    def __init__(self, payment_id, payment_method, amount):
        self.payment_id = payment_id
        self.payment_method = payment_method
        self.amount = amount
        self.status = PaymentStatus.PENDING

    def process_payment(self):
        # Process payment logic
        self.status = PaymentStatus.COMPLETED