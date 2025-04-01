from split import Split
from user import User

class ExactSplit(Split):
    def __init__(self, user: User, amount: float):
        super().__init__(user)
        self.amount = amount

    def get_amount(self) -> float:
        return self.amount
