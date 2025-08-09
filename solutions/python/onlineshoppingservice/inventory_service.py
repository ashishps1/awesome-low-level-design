from typing import Dict
from collections import defaultdict
from threading import Lock
from product import Product
from order_line_item import OrderLineItem
from exceptions import OutOfStockException
from typing import List
import threading

class InventoryService:
    def __init__(self):
        self.stock: Dict[str, int] = defaultdict(int)
        self.lock = threading.Lock()

    def add_stock(self, product: Product, quantity: int) -> None:
        with self.lock:
            self.stock[product.get_id()] += quantity

    def update_stock_for_order(self, items: List[OrderLineItem]) -> None:
        with self.lock:
            # First, check if all items are in stock
            for item in items:
                if self.stock[item.get_product_id()] < item.get_quantity():
                    raise OutOfStockException(f"Not enough stock for product ID: {item.get_product_id()}")
            
            # If all checks pass, deduct the stock
            for item in items:
                self.stock[item.get_product_id()] -= item.get_quantity()