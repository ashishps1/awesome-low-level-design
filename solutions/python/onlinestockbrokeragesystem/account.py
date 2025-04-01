from portfolio import Portfolio
from exceptions import InsufficientFundsException

class Account:
    def __init__(self, account_id, user, initial_balance):
        self.account_id = account_id
        self.user = user
        self.balance = initial_balance
        self.portfolio = Portfolio(self)

    def deposit(self, amount):
        self.balance += amount

    def withdraw(self, amount):
        if self.balance >= amount:
            self.balance -= amount
        else:
            raise InsufficientFundsException("Insufficient funds in the account.")

    def get_account_id(self):
        return self.account_id

    def get_user(self):
        return self.user

    def get_balance(self):
        return self.balance

    def get_portfolio(self):
        return self.portfolio