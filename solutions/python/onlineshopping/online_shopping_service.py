import uuid
from typing import List, Dict
from collections import defaultdict
from product import Product
from user import User
from order import Order
from shopping_cart import ShoppingCart
from order_status import OrderStatus
from payment import Payment

class OnlineShoppingService:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.users = {}
            cls._instance.products = {}
            cls._instance.orders = {}
        return cls._instance

    def register_user(self, user: User):
        self.users[user.id] = user

    def get_user(self, user_id: str) -> User:
        return self.users.get(user_id)

    def add_product(self, product: Product):
        self.products[product.id] = product

    def get_product(self, product_id: str) -> Product:
        return self.products.get(product_id)

    def search_products(self, keyword: str) -> List[Product]:
        return [product for product in self.products.values() if keyword.lower() in product.name.lower()]

    def place_order(self, user: User, cart: ShoppingCart, payment: Payment) -> Order:
        order_items = []
        for item in cart.get_items():
            product = item.product
            quantity = item.quantity
            if product.is_available(quantity):
                product.update_quantity(-quantity)
                order_items.append(item)

        if not order_items:
            raise Exception("No available products in the cart.")

        order_id = self._generate_order_id()
        order = Order(order_id, user, order_items, self._calculate_total_amount(order_items))
        self.orders[order_id] = order
        user.add_order(order)
        cart.clear()

        if payment.process_payment(order.total_amount):
            order.status = OrderStatus.PROCESSING
        else:
            order.status = OrderStatus.CANCELLED
            for item in order_items:
                item.product.update_quantity(item.quantity)

        return order

    def get_order(self, order_id: str) -> Order:
        return self.orders.get(order_id)

    def _generate_order_id(self) -> str:
        return "ORDER" + str(uuid.uuid4()).split('-')[0].upper()

    def _calculate_total_amount(self, items: List) -> float:
        return sum(item.product.price * item.quantity for item in items)
