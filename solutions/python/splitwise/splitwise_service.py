from typing import Dict
from user import User
from group import Group
from expense import Expense
from split import Split
from equal_split import EqualSplit
from percent_split import PercentSplit
from transaction import Transaction
from typing import Dict

class SplitwiseService:
    _instance = None
    _TRANSACTION_ID_PREFIX = "TXN"
    _transaction_counter = 0

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.users: Dict[str, User] = {}
            cls._instance.groups: Dict[str, Group] = {}
        return cls._instance

    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

    def add_user(self, user: User):
        self.users[user.get_id()] = user

    def add_group(self, group: Group):
        self.groups[group.get_id()] = group

    def add_expense(self, group_id: str, expense: Expense):
        group = self.groups.get(group_id)
        if group:
            group.add_expense(expense)
            self._split_expense(expense)
            self._update_balances(expense)

    def _split_expense(self, expense: Expense):
        total_amount = expense.get_amount()
        splits = expense.get_splits()
        total_splits = len(splits)

        split_amount = total_amount / total_splits
        for split in splits:
            if isinstance(split, EqualSplit):
                split.set_amount(split_amount)
            elif isinstance(split, PercentSplit):
                split.set_amount(total_amount * split.get_percent() / 100.0)

    def _update_balances(self, expense: Expense):
        for split in expense.get_splits():
            paid_by = expense.get_paid_by()
            user = split.get_user()
            amount = split.get_amount()

            if paid_by != user:
                self._update_balance(paid_by, user, amount)
                self._update_balance(user, paid_by, -amount)

    def _update_balance(self, user1: User, user2: User, amount: float):
        key = self._get_balance_key(user1, user2)
        user1.get_balances()[key] = user1.get_balances().get(key, 0.0) + amount

    def _get_balance_key(self, user1: User, user2: User) -> str:
        return f"{user1.get_id()}:{user2.get_id()}"

    def settle_balance(self, user_id1: str, user_id2: str):
        user1 = self.users.get(user_id1)
        user2 = self.users.get(user_id2)

        if user1 and user2:
            key = self._get_balance_key(user1, user2)
            balance = user1.get_balances().get(key, 0.0)

            if balance > 0:
                self._create_transaction(user1, user2, balance)
                user1.get_balances()[key] = 0.0
                user2.get_balances()[self._get_balance_key(user2, user1)] = 0.0
            elif balance < 0:
                self._create_transaction(user2, user1, abs(balance))
                user1.get_balances()[key] = 0.0
                user2.get_balances()[self._get_balance_key(user2, user1)] = 0.0

    def _create_transaction(self, sender: User, receiver: User, amount: float):
        transaction_id = self._generate_transaction_id()
        transaction = Transaction(transaction_id, sender, receiver, amount)
        # Process the transaction
        # ...

    def _generate_transaction_id(self) -> str:
        self._transaction_counter += 1
        return f"{self._TRANSACTION_ID_PREFIX}{self._transaction_counter:06d}"