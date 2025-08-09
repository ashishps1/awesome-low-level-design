import threading
from typing import Dict, List, Optional
from customer import Customer
from delivery_agent import DeliveryAgent
from delivery_assignment_strategy import DeliveryAssignmentStrategy
from order import Order
from restaurant import Restaurant
from restaurant_search_strategy import RestaurantSearchStrategy
from order_status import OrderStatus
from address import Address
from order_item import OrderItem
from menu import Menu

class FoodDeliveryService:
    _instance = None
    _lock = threading.Lock()

    def __init__(self):
        if FoodDeliveryService._instance is not None:
            raise Exception("This class is a singleton!")
        self.customers: Dict[str, Customer] = {}
        self.restaurants: Dict[str, Restaurant] = {}
        self.delivery_agents: Dict[str, DeliveryAgent] = {}
        self.orders: Dict[str, Order] = {}
        self.assignment_strategy: Optional[DeliveryAssignmentStrategy] = None

    @staticmethod
    def get_instance():
        if FoodDeliveryService._instance is None:
            with FoodDeliveryService._lock:
                if FoodDeliveryService._instance is None:
                    FoodDeliveryService._instance = FoodDeliveryService()
        return FoodDeliveryService._instance

    def set_assignment_strategy(self, assignment_strategy: DeliveryAssignmentStrategy):
        self.assignment_strategy = assignment_strategy

    def register_customer(self, name: str, phone: str, address: Address) -> Customer:
        customer = Customer(name, phone, address)
        self.customers[customer.get_id()] = customer
        return customer

    def register_restaurant(self, name: str, address: Address) -> Restaurant:
        restaurant = Restaurant(name, address)
        self.restaurants[restaurant.get_id()] = restaurant
        return restaurant

    def register_delivery_agent(self, name: str, phone: str, initial_location: Address) -> DeliveryAgent:
        delivery_agent = DeliveryAgent(name, phone, initial_location)
        self.delivery_agents[delivery_agent.get_id()] = delivery_agent
        return delivery_agent

    def place_order(self, customer_id: str, restaurant_id: str, items: List[OrderItem]) -> Order:
        customer = self.customers.get(customer_id)
        restaurant = self.restaurants.get(restaurant_id)
        if customer is None or restaurant is None:
            raise KeyError("Customer or Restaurant not found.")

        order = Order(customer, restaurant, items)
        self.orders[order.get_id()] = order
        customer.add_order_to_history(order)
        print(f"Order {order.get_id()} placed by {customer.get_name()} at {restaurant.get_name()}.")
        order.set_status(OrderStatus.PENDING)
        return order

    def update_order_status(self, order_id: str, new_status: OrderStatus):
        order = self.orders.get(order_id)
        if order is None:
            raise KeyError("Order not found.")

        order.set_status(new_status)

        if new_status == OrderStatus.READY_FOR_PICKUP:
            self.assign_delivery(order)

    def cancel_order(self, order_id: str):
        order = self.orders.get(order_id)
        if order is None:
            print(f"ERROR: Order with ID {order_id} not found.")
            return

        if order.cancel():
            print(f"SUCCESS: Order {order_id} has been successfully canceled.")
        else:
            print(f"FAILED: Order {order_id} could not be canceled. Its status is: {order.get_status().value}")

    def assign_delivery(self, order: Order):
        available_agents = list(self.delivery_agents.values())

        best_agent = self.assignment_strategy.find_agent(order, available_agents)
        if best_agent:
            order.assign_delivery_agent(best_agent)
            distance = best_agent.get_current_location().distance_to(order.get_restaurant().get_address())
            print(f"Agent {best_agent.get_name()} (dist: {distance:.2f}) assigned to order {order.get_id()}.")
            order.set_status(OrderStatus.OUT_FOR_DELIVERY)
        else:
            print(f"No available delivery agents found for order {order.get_id()}")

    def search_restaurants(self, strategies: List[RestaurantSearchStrategy]) -> List[Restaurant]:
        results = list(self.restaurants.values())

        for strategy in strategies:
            results = strategy.filter(results)

        return results

    def get_restaurant_menu(self, restaurant_id: str) -> Menu:
        restaurant = self.restaurants.get(restaurant_id)
        if restaurant is None:
            raise KeyError(f"Restaurant with ID {restaurant_id} not found.")
        return restaurant.get_menu()