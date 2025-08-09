import uuid

class User:
    def __init__(self, name: str, email: str):
        self.id = str(uuid.uuid4())
        self.name = name
        self.email = email

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name