from split import Split
from user import User

class PercentSplit(Split):
    def __init__(self, user: User, percent: float):
        super().__init__(user)
        self.percent = percent

    def get_amount(self) -> float:
        return self.amount

    def get_percent(self) -> float:
        return self.percent