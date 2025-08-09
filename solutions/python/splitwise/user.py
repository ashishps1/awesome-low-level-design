import uuid
from balance_sheet import BalanceSheet
    
class User:
    def __init__(self, name: str, email: str):
        self._id = str(uuid.uuid4())
        self._name = name
        self._email = email
        self._balance_sheet = BalanceSheet(self)
    
    def get_id(self) -> str:
        return self._id
    
    def get_name(self) -> str:
        return self._name
    
    def get_balance_sheet(self) -> 'BalanceSheet':
        return self._balance_sheet