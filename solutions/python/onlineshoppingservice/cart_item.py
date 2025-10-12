from product import Product
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from product import Product

class CartItem:
    def __init__(self, product: Product, quantity: int):
        self.product = product
        self.quantity = quantity

    def get_product(self) -> Product:
        return self.product

    def get_quantity(self) -> int:
        return self.quantity

    def increment_quantity(self, amount: int) -> None:
        self.quantity += amount

    def get_price(self) -> float:
        return self.product.get_price() * self.quantity