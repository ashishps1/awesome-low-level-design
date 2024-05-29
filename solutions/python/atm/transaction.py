from abc import ABC, abstractmethod

class Transaction(ABC):
    def __init__(self, transaction_id, account, amount):
        self.transaction_id = transaction_id
        self.account = account
        self.amount = amount

    @abstractmethod
    def execute(self):
        pass