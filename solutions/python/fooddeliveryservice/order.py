import uuid
from order_item import OrderItem
from order_status import OrderStatus
from customer import Customer
from restaurant import Restaurant
from delivery_agent import DeliveryAgent
from typing import List, Optional
from typing import TYPE_CHECKING
from order_observer import OrderObserver    

class Order:
    def __init__(self, customer: Customer, restaurant: Restaurant, items: List[OrderItem]):
        self.id = str(uuid.uuid4())
        self.customer = customer
        self.restaurant = restaurant
        self.items = items
        self.status = OrderStatus.PENDING
        self.delivery_agent: Optional[DeliveryAgent] = None
        self.observers: List[OrderObserver] = []
        self.add_observer(customer)
        self.add_observer(restaurant)

    def add_observer(self, observer: OrderObserver):
        self.observers.append(observer)

    def notify_observers(self):
        for observer in self.observers:
            observer.on_update(self)

    def set_status(self, new_status: OrderStatus):
        if self.status != new_status:
            self.status = new_status
            self.notify_observers()

    def cancel(self) -> bool:
        if self.status == OrderStatus.PENDING:
            self.set_status(OrderStatus.CANCELLED)
            return True
        return False

    def assign_delivery_agent(self, agent: DeliveryAgent):
        self.delivery_agent = agent
        self.add_observer(agent)
        agent.set_available(False)

    def get_id(self) -> str:
        return self.id

    def get_status(self) -> OrderStatus:
        return self.status

    def get_customer(self) -> Customer:
        return self.customer

    def get_restaurant(self) -> Restaurant:
        return self.restaurant

    def get_delivery_agent(self) -> Optional[DeliveryAgent]:
        return self.delivery_agent