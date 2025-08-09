import threading
from dispense_chain import DispenseChain

class CashDispenser:
    def __init__(self, chain: DispenseChain):
        self._chain = chain
        self._lock = threading.Lock()
    
    def dispense_cash(self, amount: int):
        with self._lock:
            self._chain.dispense(amount)
    
    def can_dispense_cash(self, amount: int) -> bool:
        with self._lock:
            if amount % 10 != 0:
                return False
            return self._chain.can_dispense(amount)