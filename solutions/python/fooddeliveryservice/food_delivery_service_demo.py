from food_delivery_service import FoodDeliveryService
from customer import Customer
from restaurant import Restaurant
from menu_item import MenuItem
from order_item import OrderItem
from delivery_agent import DeliveryAgent
from order import OrderStatus

class FoodDeliveryServiceDemo:
    @staticmethod
    def run():
        service = FoodDeliveryService.get_instance()

        # Register customers
        customer1 = Customer("C001", "Alice Johnson", "alice@example.com", "555-1234")
        customer2 = Customer("C002", "Bob Smith", "bob@example.com", "555-5678")
        service.register_customer(customer1)
        service.register_customer(customer2)

        # Register restaurants
        menu1 = [
            MenuItem("M001", "Pizza", "Cheese Pizza", 10.0),
            MenuItem("M002", "Burger", "Beef Burger", 8.0),
        ]
        menu2 = [
            MenuItem("M003", "Sushi", "Salmon Sushi", 12.0),
            MenuItem("M004", "Ramen", "Tonkotsu Ramen", 15.0),
        ]
        restaurant1 = Restaurant("R001", "Pizza Place", "123 Main St", menu1)
        restaurant2 = Restaurant("R002", "Sushi House", "456 Oak St", menu2)
        service.register_restaurant(restaurant1)
        service.register_restaurant(restaurant2)

        # Register delivery agents
        agent1 = DeliveryAgent("D001", "Charlie Brown", "555-8765")
        agent2 = DeliveryAgent("D002", "Daisy Duck", "555-4321")
        service.register_delivery_agent(agent1)
        service.register_delivery_agent(agent2)

        # Place an order
        items = [OrderItem(menu1[0], 2), OrderItem(menu1[1], 1)]
        order = service.place_order(customer1.id, restaurant1.id, items)
        if order:
            print(f"Order placed: {order.id}")

        # Update order status
        service.update_order_status(order.id, OrderStatus.CONFIRMED)
        print(f"Order status updated to {OrderStatus.CONFIRMED}")

        # Check order details
        print(f"Order details: {order.id}, status: {order.status}, items: {[(item.item.name, item.quantity) for item in order._items]}")

        # Check available restaurants
        available_restaurants = service.get_available_restaurants()
        print("Available restaurants:")
        for restaurant in available_restaurants:
            print(f"- {restaurant.name}")

        # Cancel an order
        service.cancel_order(order.id)
        print(f"Order cancelled: {order.id}")

if __name__ == "__main__":
    FoodDeliveryServiceDemo.run()
