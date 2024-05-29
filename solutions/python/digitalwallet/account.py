from decimal import Decimal
from exception import InsufficientFundsException

class Account:
    def __init__(self, id, user, account_number, currency):
        self.id = id
        self.user = user
        self.account_number = account_number
        self.currency = currency
        self.balance = Decimal('0.00')
        self.transactions = []

    def deposit(self, amount):
        self.balance += amount

    def withdraw(self, amount):
        if self.balance >= amount:
            self.balance -= amount
        else:
            raise InsufficientFundsException("Insufficient funds in the account.")

    def add_transaction(self, transaction):
        self.transactions.append(transaction)
