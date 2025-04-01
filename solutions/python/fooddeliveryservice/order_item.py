from menu_item import MenuItem

class OrderItem:
    def __init__(self, item: 'MenuItem', quantity: int):
        self._item = item
        self._quantity = quantity

    @property
    def item(self) -> 'MenuItem':
        return self._item

    @property
    def quantity(self) -> int:
        return self._quantity

    @quantity.setter
    def quantity(self, quantity: int):
        self._quantity = quantity
