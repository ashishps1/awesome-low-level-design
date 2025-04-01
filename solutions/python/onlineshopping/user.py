from typing import List

class User:
    def __init__(self, user_id: str, name: str, email: str, password: str):
        self._id = user_id
        self._name = name
        self._email = email
        self._password = password
        self._orders = []

    def add_order(self, order):
        self._orders.append(order)

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
    def password(self) -> str:
        return self._password

    @property
    def orders(self) -> List:
        return self._orders