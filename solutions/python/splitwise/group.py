import uuid
from typing import List, TYPE_CHECKING

if TYPE_CHECKING:
    from user import User

class Group:
    def __init__(self, name: str, members: List['User']):
        self._id = str(uuid.uuid4())
        self._name = name
        self._members = members
    
    def get_id(self) -> str:
        return self._id
    
    def get_name(self) -> str:
        return self._name
    
    def get_members(self) -> List['User']:
        return self._members.copy()