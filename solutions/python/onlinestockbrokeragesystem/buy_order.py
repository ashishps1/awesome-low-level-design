from order import Order, OrderStatus
from exceptions import InsufficientFundsException

class BuyOrder(Order):
    def __init__(self, order_id, account, stock, quantity, price):
        super().__init__(order_id, account, stock, quantity, price)

    def execute(self):
        total_cost = self.quantity * self.price
        if self.account.get_balance() >= total_cost:
            self.account.withdraw(total_cost)
            # Update portfolio and perform necessary actions
            self.status = OrderStatus.EXECUTED
        else:
            self.status = OrderStatus.REJECTED
            raise InsufficientFundsException("Insufficient funds to execute the buy order.")