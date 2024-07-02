from typing import Dict, List
from order_item import OrderItem
from product import Product

class ShoppingCart:
    def __init__(self):
        self._items: Dict[str, OrderItem] = {}

    def add_item(self, product: Product, quantity: int):
        product_id = product.id
        if product_id in self._items:
            item = self._items[product_id]
            quantity += item.quantity
        self._items[product_id] = OrderItem(product, quantity)

    def remove_item(self, product_id: str):
        if product_id in self._items:
            del self._items[product_id]

    def update_item_quantity(self, product_id: str, quantity: int):
        if product_id in self._items:
            item = self._items[product_id]
            self._items[product_id] = OrderItem(item.product, quantity)

    def get_items(self) -> List[OrderItem]:
        return list(self._items.values())

    def clear(self):
        self._items.clear()