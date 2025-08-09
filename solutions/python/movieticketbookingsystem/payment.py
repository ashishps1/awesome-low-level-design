import uuid
from enums import PaymentStatus

class Payment:
    def __init__(self, amount: float, status: PaymentStatus, transaction_id: str):
        self.id = str(uuid.uuid4())
        self.amount = amount
        self.status = status
        self.transaction_id = transaction_id

    def get_status(self) -> PaymentStatus:
        return self.status