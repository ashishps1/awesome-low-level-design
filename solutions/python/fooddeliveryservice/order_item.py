from menu_item import MenuItem

class OrderItem:
    def __init__(self, item: MenuItem, quantity: int):
        self.item = item
        self.quantity = quantity

    def get_item(self) -> MenuItem:
        return self.item

    def get_quantity(self) -> int:
        return self.quantity