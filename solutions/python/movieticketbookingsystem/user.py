class User:
    def __init__(self, user_id: str, name: str, email: str):
        self._id = user_id
        self._name = name
        self._email = email

    @property
    def id(self) -> str:
        return self._id

    @property
    def name(self) -> str:
        return self._name

    @property
    def email(self) -> str:
        return self._email
