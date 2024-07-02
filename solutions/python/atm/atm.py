import datetime
import threading
from withdrawal_transaction import WithdrawalTransaction
from deposit_transaction import DepositTransaction

class ATM:
    def __init__(self, banking_service, cash_dispenser):
        self.banking_service = banking_service
        self.cash_dispenser = cash_dispenser
        self.transaction_counter = 0
        self.transaction_lock = threading.Lock()

    def authenticate_user(self, card):
        # Authenticate user using card and PIN
        # ...
        pass

    def check_balance(self, account_number):
        account = self.banking_service.get_account(account_number)
        return account.get_balance()

    def withdraw_cash(self, account_number, amount):
        account = self.banking_service.get_account(account_number)
        transaction = WithdrawalTransaction(self.generate_transaction_id(), account, amount)
        self.banking_service.process_transaction(transaction)
        self.cash_dispenser.dispense_cash(int(amount))

    def deposit_cash(self, account_number, amount):
        account = self.banking_service.get_account(account_number)
        transaction = DepositTransaction(self.generate_transaction_id(), account, amount)
        self.banking_service.process_transaction(transaction)

    def generate_transaction_id(self):
        with self.transaction_lock:
            self.transaction_counter += 1
            timestamp = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
            return f"TXN{timestamp}{self.transaction_counter:010d}"