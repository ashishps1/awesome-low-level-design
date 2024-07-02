from typing import List
from user import User
from expense import Expense

class Group:
    def __init__(self, group_id: str, name: str):
        self.id = group_id
        self.name = name
        self.members: List[User] = []
        self.expenses: List[Expense] = []

    def add_member(self, user: User):
        self.members.append(user)

    def add_expense(self, expense: Expense):
        self.expenses.append(expense)

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name

    def get_members(self) -> List[User]:
        return self.members

    def get_expenses(self) -> List[Expense]:
        return self.expenses