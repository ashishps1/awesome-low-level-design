from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from user import User

class Split:
    def __init__(self, user: 'User', amount: float):
        self._user = user
        self._amount = amount
    
    def get_user(self) -> 'User':
        return self._user
    
    def get_amount(self) -> float:
        return self._amount