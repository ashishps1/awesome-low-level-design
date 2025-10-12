from typing import Dict
from cart_item import CartItem
from product import Product

class ShoppingCart:
    def __init__(self):
        self.items: Dict[str, CartItem] = {}

    def add_item(self, product: Product, quantity: int) -> None:
        if product.get_id() in self.items:
            self.items[product.get_id()].increment_quantity(quantity)
        else:
            self.items[product.get_id()] = CartItem(product, quantity)

    def remove_item(self, product_id: str) -> None:
        if product_id in self.items:
            del self.items[product_id]

    def get_items(self) -> Dict[str, CartItem]:
        return self.items.copy()

    def calculate_total(self) -> float:
        return sum(item.get_price() for item in self.items.values())

    def clear_cart(self) -> None:
        self.items.clear()