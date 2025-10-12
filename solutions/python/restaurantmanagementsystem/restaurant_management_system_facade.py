import threading
from typing import Dict, List
from restaurant import Restaurant
from table import Table
from staff import Chef, Waiter
from menu_item import MenuItem
from order import Order
from order_item import OrderItem
from command import PrepareOrderCommand, ServeOrderCommand
from decorators import TaxDecorator, ServiceChargeDecorator
from bill import Bill, BaseBill

class RestaurantManagementSystemFacade:
    _instance = None
    _lock = threading.Lock()
    
    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    cls._instance._initialized = False
        return cls._instance
    
    def __init__(self):
        if not self._initialized:
            self._restaurant = Restaurant.get_instance()
            self._order_id_counter = 1
            self._orders: Dict[int, Order] = {}
            self._initialized = True
    
    @classmethod
    def get_instance(cls):
        return cls()
    
    def add_table(self, table_id: int, capacity: int) -> Table:
        table = Table(table_id, capacity)
        self._restaurant.add_table(table)
        return table
    
    def add_waiter(self, waiter_id: str, name: str) -> Waiter:
        waiter = Waiter(waiter_id, name)
        self._restaurant.add_waiter(waiter)
        return waiter
    
    def add_chef(self, chef_id: str, name: str) -> Chef:
        chef = Chef(chef_id, name)
        self._restaurant.add_chef(chef)
        return chef
    
    def add_menu_item(self, item_id: str, name: str, price: float) -> MenuItem:
        item = MenuItem(item_id, name, price)
        self._restaurant.menu.add_item(item)
        return item
    
    def take_order(self, table_id: int, waiter_id: str, menu_item_ids: List[str]) -> Order:
        waiter = self._restaurant.get_waiter(waiter_id)
        if waiter is None:
            raise ValueError("Invalid waiter ID.")
        
        # For simplicity, we get the first available chef
        chefs = self._restaurant.get_chefs()
        if not chefs:
            raise RuntimeError("No chefs available.")
        chef = chefs[0]
        
        order = Order(self._order_id_counter, table_id)
        self._order_id_counter += 1
        
        for item_id in menu_item_ids:
            menu_item = self._restaurant.menu.get_item(item_id)
            order_item = OrderItem(menu_item, order)
            # Waiter subscribes to each item to get notified when it's ready
            order_item.add_observer(waiter)
            order.add_item(order_item)
        
        # The Command pattern decouples the waiter (invoker) from the chef (receiver)
        prepare_order_command = PrepareOrderCommand(order, chef)
        prepare_order_command.execute()
        
        self._orders[order.order_id] = order
        return order
    
    def mark_items_as_ready(self, order_id: int):
        order = self._orders[order_id]
        print(f"\nChef has finished preparing order {order.order_id}")
        
        for item in order.order_items:
            # Preparing -> ReadyForPickup -> Notifies Observer (Waiter)
            item.next_state()
            item.next_state()
    
    def serve_order(self, waiter_id: str, order_id: int):
        order = self._orders[order_id]
        waiter = self._restaurant.get_waiter(waiter_id)
        
        serve_order_command = ServeOrderCommand(order, waiter)
        serve_order_command.execute()
    
    def generate_bill(self, order_id: int) -> Bill:
        order = self._orders[order_id]
        # The Decorator pattern adds charges dynamically
        bill_component = BaseBill(order)
        bill_component = TaxDecorator(bill_component, 0.08)  # 8% tax
        bill_component = ServiceChargeDecorator(bill_component, 5.00)  # $5 flat service charge
        
        return Bill(bill_component)