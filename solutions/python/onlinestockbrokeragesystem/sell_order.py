from order import Order, OrderStatus

class SellOrder(Order):
    def __init__(self, order_id, account, stock, quantity, price):
        super().__init__(order_id, account, stock, quantity, price)

    def execute(self):
        # Check if the user has sufficient quantity of the stock to sell
        # Update portfolio and perform necessary actions
        total_proceeds = self.quantity * self.price
        self.account.deposit(total_proceeds)
        self.status = OrderStatus.EXECUTED