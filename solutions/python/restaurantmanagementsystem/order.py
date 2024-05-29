from enum import Enum
from datetime import datetime

class OrderStatus(Enum):
    PENDING = 1
    PREPARING = 2
    READY = 3
    COMPLETED = 4
    CANCELLED = 5

class Order:
    def __init__(self, id, items, total_amount, status, timestamp):
        self.id = id
        self.items = items
        self.total_amount = total_amount
        self.status = status
        self.timestamp = timestamp

    def set_status(self, status):
        self.status = status

    def get_id(self):
        return self.id

    def get_items(self):
        return self.items

    def get_total_amount(self):
        return self.total_amount

    def get_status(self):
        return self.status

    def get_timestamp(self):
        return self.timestamp