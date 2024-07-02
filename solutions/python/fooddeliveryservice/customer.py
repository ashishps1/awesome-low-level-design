class Customer:
    def __init__(self, customer_id: str, name: str, email: str, phone: str):
        self._id = customer_id
        self._name = name
        self._email = email
        self._phone = phone

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
    def phone(self) -> str:
        return self._phone
