from enum import Enum
from typing import List

class OrderStatus(Enum):
    PENDING = "PENDING"
    CONFIRMED = "CONFIRMED"
    PREPARING = "PREPARING"
    OUT_FOR_DELIVERY = "OUT_FOR_DELIVERY"
    DELIVERED = "DELIVERED"
    CANCELLED = "CANCELLED"

class Order:
    def __init__(self, order_id: str, customer, restaurant):
        self._id = order_id
        self._customer = customer
        self._restaurant = restaurant
        self._items = []
        self._status = OrderStatus.PENDING
        self._delivery_agent = None

    @property
    def id(self) -> str:
        return self._id

    @property
    def status(self) -> OrderStatus:
        return self._status

    def add_item(self, item):
        self._items.append(item)

    def remove_item(self, item):
        self._items.remove(item)

    def set_status(self, status: OrderStatus):
        self._status = status

    def assign_delivery_agent(self, agent):
        self._delivery_agent = agent
