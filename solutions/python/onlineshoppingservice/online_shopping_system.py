from typing import Dict, List, Optional
from product import Product
from customer import Customer
from order import Order
from inventory_service import InventoryService
from payment_service import PaymentService
from order_service import OrderService
from search_service import SearchService
from payment_strategy import PaymentStrategy
from address import Address
import threading
from shopping_cart import ShoppingCart

class OnlineShoppingSystem:
    _instance = None
    _lock = threading.Lock()

    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self):
        if hasattr(self, 'initialized'):
            return
        
        self.products: Dict[str, Product] = {}
        self.customers: Dict[str, Customer] = {}
        self.orders: Dict[str, Order] = {}
        
        self.inventory_service = InventoryService()
        self.payment_service = PaymentService()
        self.order_service = OrderService(self.inventory_service)
        self.search_service = SearchService(self.products.values())
        
        self.initialized = True

    @classmethod
    def get_instance(cls) -> 'OnlineShoppingSystem':
        return cls()

    def add_product(self, product: Product, initial_stock: int) -> None:
        self.products[product.get_id()] = product
        self.inventory_service.add_stock(product, initial_stock)

    def register_customer(self, name: str, email: str, password: str, address: Address) -> Customer:
        customer = Customer(name, email, password, address)
        self.customers[customer.get_id()] = customer
        return customer

    def add_to_cart(self, customer_id: str, product_id: str, quantity: int) -> None:
        customer = self.customers[customer_id]
        product = self.products[product_id]
        customer.get_account().get_cart().add_item(product, quantity)

    def get_customer_cart(self, customer_id: str) -> ShoppingCart:
        customer = self.customers[customer_id]
        return customer.get_account().get_cart()

    def search_products(self, name: str) -> List[Product]:
        return self.search_service.search_by_name(name)

    def place_order(self, customer_id: str, payment_strategy: PaymentStrategy) -> Optional[Order]:
        customer = self.customers[customer_id]
        cart = customer.get_account().get_cart()
        
        if not cart.get_items():
            print("Cannot place an order with an empty cart.")
            return None

        # 1. Process payment
        payment_success = self.payment_service.process_payment(payment_strategy, cart.calculate_total())
        if not payment_success:
            print("Payment failed. Please try again.")
            return None

        # 2. Create order and update inventory
        try:
            order = self.order_service.create_order(customer, cart)
            self.orders[order.get_id()] = order

            # 3. Clear the cart
            cart.clear_cart()

            return order
        except Exception as e:
            print(f"Order placement failed: {e}")
            return None