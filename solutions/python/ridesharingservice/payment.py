from enum import Enum

class PaymentStatus(Enum):
    PENDING = 1
    COMPLETED = 2
    FAILED = 3

class Payment:
    def __init__(self, id, ride, amount, status):
        self.id = id
        self.ride = ride
        self.amount = amount
        self.status = status