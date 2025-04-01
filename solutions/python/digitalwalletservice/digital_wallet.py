import uuid
from user import User
from account import Account
from payment_method import PaymentMethod
from currency import Currency
from currency_converter import CurrencyConverter
from transaction import Transaction

class DigitalWallet:
    _instance = None

    def __init__(self):
        self.users = {}
        self.accounts = {}
        self.payment_methods = {}

    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

    def create_user(self, user):
        self.users[user.id] = user

    def get_user(self, user_id):
        return self.users.get(user_id)

    def create_account(self, account):
        self.accounts[account.id] = account
        account.user.add_account(account)

    def get_account(self, account_id):
        return self.accounts.get(account_id)

    def add_payment_method(self, payment_method):
        self.payment_methods[payment_method.id] = payment_method

    def get_payment_method(self, payment_method_id):
        return self.payment_methods.get(payment_method_id)

    def transfer_funds(self, source_account, destination_account, amount, currency):
        if source_account.currency != currency:
            amount = CurrencyConverter.convert(amount, currency, source_account.currency)
        source_account.withdraw(amount)

        if destination_account.currency != currency:
            amount = CurrencyConverter.convert(amount, currency, destination_account.currency)
        destination_account.deposit(amount)

        transaction_id = self._generate_transaction_id()
        transaction = Transaction(transaction_id, source_account, destination_account, amount, currency)
        source_account.add_transaction(transaction)
        destination_account.add_transaction(transaction)

    def get_transaction_history(self, account):
        return account.transactions

    def _generate_transaction_id(self):
        return "TXN" + str(uuid.uuid4()).replace('-', '').upper()[:8]
