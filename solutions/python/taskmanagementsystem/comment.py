import uuid
from datetime import datetime
from user import User

class Comment:
    def __init__(self, content: str, author: User):
        self._id = str(uuid.uuid4())
        self._content = content
        self._author = author
        self._timestamp = datetime.now()
    
    @property
    def author(self) -> User:
        return self._author