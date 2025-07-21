from transaction import Transaction
from account import Account

class WithdrawalTransaction(Transaction):
    def __init__(self, transaction_id, account, amount):
        super().__init__(transaction_id, account, amount)

    def execute(self):
        self.account.debit(self.amount)