from enum import Enum

class OrderStatus(Enum):
    PENDING = 0
    EXECUTED = 1
    REJECTED = 2

class Order:
    def __init__(self, order_id, account, stock, quantity, price):
        self.order_id = order_id
        self.account = account
        self.stock = stock
        self.quantity = quantity
        self.price = price
        self.status = OrderStatus.PENDING

    def execute(self):
        pass