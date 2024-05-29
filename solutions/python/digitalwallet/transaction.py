from datetime import datetime

class Transaction:
    def __init__(self, id, source_account, destination_account, amount, currency):
        self.id = id
        self.source_account = source_account
        self.destination_account = destination_account
        self.amount = amount
        self.currency = currency
        self.timestamp = datetime.now()
