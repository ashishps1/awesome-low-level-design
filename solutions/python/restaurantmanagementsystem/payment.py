from enum import Enum

class PaymentMethod(Enum):
    CASH = 1
    CREDIT_CARD = 2
    MOBILE_PAYMENT = 3

class PaymentStatus(Enum):
    PENDING = 1
    COMPLETED = 2
    FAILED = 3

class Payment:
    def __init__(self, id, amount, method, status):
        self.id = id
        self.amount = amount
        self.method = method
        self.status = status

    def get_id(self):
        return self.id

    def get_amount(self):
        return self.amount

    def get_method(self):
        return self.method

    def get_status(self):
        return self.status