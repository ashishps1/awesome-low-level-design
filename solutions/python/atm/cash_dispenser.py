import threading

class CashDispenser:
    def __init__(self, initial_cash):
        self.cash_available = initial_cash
        self.lock = threading.Lock()

    def dispense_cash(self, amount):
        with self.lock:
            if amount > self.cash_available:
                raise ValueError("Insufficient cash available in the ATM.")
            self.cash_available -= amount
            print("Cash dispensed:", amount)