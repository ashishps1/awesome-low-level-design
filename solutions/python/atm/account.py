import threading
from typing import Dict
from card import Card

class Account:
    def __init__(self, account_number: str, balance: float):
        self._account_number = account_number
        self._balance = balance
        self._cards: Dict[str, Card] = {}
        self._lock = threading.Lock()
    
    def get_account_number(self) -> str:
        return self._account_number
    
    def get_balance(self) -> float:
        return self._balance
    
    def get_cards(self) -> Dict[str, Card]:
        return self._cards
    
    def deposit(self, amount: float):
        with self._lock:
            self._balance += amount
    
    def withdraw(self, amount: float) -> bool:
        with self._lock:
            if self._balance >= amount:
                self._balance -= amount
                return True
            return False