from typing import List
from user import User
from split import Split

class Expense:
    def __init__(self, expense_id: str, amount: float, description: str, paid_by: User):
        self.id = expense_id
        self.amount = amount
        self.description = description
        self.paid_by = paid_by
        self.splits: List[Split] = []

    def add_split(self, split: Split):
        self.splits.append(split)

    def get_id(self) -> str:
        return self.id

    def get_amount(self) -> float:
        return self.amount

    def get_description(self) -> str:
        return self.description

    def get_paid_by(self) -> User:
        return self.paid_by

    def get_splits(self) -> List[Split]:
        return self.splits