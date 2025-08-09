import threading
from typing import Dict, List, Optional
from user import User
from group import Group
from expense import Expense
from transaction import Transaction

class SplitwiseService:
    _instance = None
    _lock = threading.Lock()
    
    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    cls._instance._initialized = False
        return cls._instance
    
    def __init__(self):
        if not self._initialized:
            self._users: Dict[str, User] = {}
            self._groups: Dict[str, Group] = {}
            self._initialized = True
    
    @classmethod
    def get_instance(cls):
        return cls()
    
    def add_user(self, name: str, email: str) -> User:
        user = User(name, email)
        self._users[user.get_id()] = user
        return user
    
    def add_group(self, name: str, members: List[User]) -> Group:
        group = Group(name, members)
        self._groups[group.get_id()] = group
        return group
    
    def get_user(self, user_id: str) -> Optional[User]:
        return self._users.get(user_id)
    
    def get_group(self, group_id: str) -> Optional[Group]:
        return self._groups.get(group_id)
    
    def create_expense(self, builder: Expense.ExpenseBuilder):
        with self._lock:
            expense = builder.build()
            paid_by = expense.get_paid_by()
            
            for split in expense.get_splits():
                participant = split.get_user()
                amount = split.get_amount()
                
                if paid_by != participant:
                    paid_by.get_balance_sheet().adjust_balance(participant, amount)
                    participant.get_balance_sheet().adjust_balance(paid_by, -amount)
            
            print(f"Expense '{expense.get_description()}' of amount {expense.get_amount()} created.")
    
    def settle_up(self, payer_id: str, payee_id: str, amount: float):
        with self._lock:
            payer = self._users[payer_id]
            payee = self._users[payee_id]
            print(f"{payer.get_name()} is settling up {amount} with {payee.get_name()}")
            
            # Settlement is like a reverse expense. payer owes less to payee.
            payee.get_balance_sheet().adjust_balance(payer, -amount)
            payer.get_balance_sheet().adjust_balance(payee, amount)
    
    def show_balance_sheet(self, user_id: str):
        user = self._users[user_id]
        user.get_balance_sheet().show_balances()
    
    def simplify_group_debts(self, group_id: str) -> List[Transaction]:
        group = self._groups.get(group_id)
        if group is None:
            raise ValueError("Group not found")
        
        # Calculate net balance for each member within the group context
        net_balances = {}
        for member in group.get_members():
            balance = 0
            for other_user, amount in member.get_balance_sheet().get_balances().items():
                # Consider only balances with other group members
                if other_user in group.get_members():
                    balance += amount
            net_balances[member] = balance
        
        # Separate into creditors and debtors
        creditors = [(user, balance) for user, balance in net_balances.items() if balance > 0]
        debtors = [(user, balance) for user, balance in net_balances.items() if balance < 0]
        
        creditors.sort(key=lambda x: x[1], reverse=True)
        debtors.sort(key=lambda x: x[1])
        
        transactions = []
        i = j = 0
        
        while i < len(creditors) and j < len(debtors):
            creditor_user, creditor_amount = creditors[i]
            debtor_user, debtor_amount = debtors[j]
            
            amount_to_settle = min(creditor_amount, -debtor_amount)
            transactions.append(Transaction(debtor_user, creditor_user, amount_to_settle))
            
            creditors[i] = (creditor_user, creditor_amount - amount_to_settle)
            debtors[j] = (debtor_user, debtor_amount + amount_to_settle)
            
            if abs(creditors[i][1]) < 0.01:
                i += 1
            if abs(debtors[j][1]) < 0.01:
                j += 1
        
        return transactions