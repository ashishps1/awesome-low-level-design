from datetime import datetime
from typing import List, Optional
from user import User
from split import Split
from split_strategy import SplitStrategy

class Expense:
    def __init__(self, builder: 'ExpenseBuilder'):
        self._id = builder._id
        self._description = builder._description
        self._amount = builder._amount
        self._paid_by = builder._paid_by
        self._timestamp = datetime.now()
        
        # Use the strategy to calculate splits
        self._splits = builder._split_strategy.calculate_splits(
            builder._amount, builder._paid_by, builder._participants, builder._split_values
        )
    
    def get_id(self) -> str:
        return self._id
    
    def get_description(self) -> str:
        return self._description
    
    def get_amount(self) -> float:
        return self._amount
    
    def get_paid_by(self) -> User:
        return self._paid_by
    
    def get_splits(self) -> List[Split]:
        return self._splits
    
    class ExpenseBuilder:
        def __init__(self):
            self._id: Optional[str] = None
            self._description: Optional[str] = None
            self._amount: Optional[float] = None
            self._paid_by: Optional[User] = None
            self._participants: Optional[List[User]] = None
            self._split_strategy: Optional[SplitStrategy] = None
            self._split_values: Optional[List[float]] = None
        
        def set_id(self, expense_id: str) -> 'Expense.ExpenseBuilder':
            self._id = expense_id
            return self
        
        def set_description(self, description: str) -> 'Expense.ExpenseBuilder':
            self._description = description
            return self
        
        def set_amount(self, amount: float) -> 'Expense.ExpenseBuilder':
            self._amount = amount
            return self
        
        def set_paid_by(self, paid_by: User) -> 'Expense.ExpenseBuilder':
            self._paid_by = paid_by
            return self
        
        def set_participants(self, participants: List[User]) -> 'Expense.ExpenseBuilder':
            self._participants = participants
            return self
        
        def set_split_strategy(self, split_strategy: SplitStrategy) -> 'Expense.ExpenseBuilder':
            self._split_strategy = split_strategy
            return self
        
        def set_split_values(self, split_values: List[float]) -> 'Expense.ExpenseBuilder':
            self._split_values = split_values
            return self
        
        def build(self) -> 'Expense':
            if self._split_strategy is None:
                raise ValueError("Split strategy is required.")
            return Expense(self)