import threading
from typing import Dict, TYPE_CHECKING

if TYPE_CHECKING:
    from user import User

class BalanceSheet:
    def __init__(self, owner: 'User'):
        self._owner = owner
        self._balances: Dict['User', float] = {}
        self._lock = threading.Lock()
    
    def get_balances(self) -> Dict['User', float]:
        return self._balances
    
    def adjust_balance(self, other_user: 'User', amount: float):
        with self._lock:
            if self._owner == other_user:
                return  # Cannot owe yourself
            
            if other_user in self._balances:
                self._balances[other_user] += amount
            else:
                self._balances[other_user] = amount
    
    def show_balances(self):
        print(f"--- Balance Sheet for {self._owner.get_name()} ---")
        if not self._balances:
            print("All settled up!")
            return
        
        total_owed_to_me = 0
        total_i_owe = 0
        
        for other_user, amount in self._balances.items():
            if amount > 0.01:
                print(f"{other_user.get_name()} owes {self._owner.get_name()} ${amount:.2f}")
                total_owed_to_me += amount
            elif amount < -0.01:
                print(f"{self._owner.get_name()} owes {other_user.get_name()} ${-amount:.2f}")
                total_i_owe += (-amount)
        
        print(f"Total Owed to {self._owner.get_name()}: ${total_owed_to_me:.2f}")
        print(f"Total {self._owner.get_name()} Owes: ${total_i_owe:.2f}")
        print("---------------------------------")