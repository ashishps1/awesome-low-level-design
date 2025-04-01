class OrderItem:
    def __init__(self, product, quantity: int):
        self._product = product
        self._quantity = quantity

    @property
    def product(self):
        return self._product

    @property
    def quantity(self) -> int:
        return self._quantity
