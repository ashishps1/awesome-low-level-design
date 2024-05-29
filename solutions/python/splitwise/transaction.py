from user import User

class Transaction:
    def __init__(self, transaction_id: str, sender: User, receiver: User, amount: float):
        self.id = transaction_id
        self.sender = sender
        self.receiver = receiver
        self.amount = amount