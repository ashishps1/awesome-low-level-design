from typing import List
from order_status import OrderStatus

class Order:
    def __init__(self, order_id: str, user, items: List, total_amount: float):
        self._id = order_id
        self._user = user
        self._items = items
        self._total_amount = total_amount
        self._status = OrderStatus.PENDING

    def calculate_total_amount(self) -> float:
        return sum(item.product.price * item.quantity for item in self._items)

    @property
    def id(self) -> str:
        return self._id

    @property
    def user(self):
        return self._user

    @property
    def items(self) -> List:
        return self._items

    @property
    def total_amount(self) -> float:
        return self._total_amount

    @property
    def status(self):
        return self._status

    @status.setter
    def status(self, status):
        self._status = status
