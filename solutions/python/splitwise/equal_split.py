from split import Split
from user import User

class EqualSplit(Split):
    def __init__(self, user: User):
        super().__init__(user)

    def get_amount(self) -> float:
        return self.amount