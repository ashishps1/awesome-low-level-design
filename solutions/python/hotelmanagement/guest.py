class Guest:
    def __init__(self, guest_id: str, name: str, email: str, phone_number: str):
        self._id = guest_id
        self._name = name
        self._email = email
        self._phone_number = phone_number

    @property
    def id(self) -> str:
        return self._id

    @property
    def name(self) -> str:
        return self._name

    @property
    def email(self) -> str:
        return self._email

    @property
    def phone_number(self) -> str:
        return self._phone_number
