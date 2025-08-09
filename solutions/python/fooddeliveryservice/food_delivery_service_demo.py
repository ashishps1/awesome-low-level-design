from food_delivery_service import FoodDeliveryService
from delivery_assignment_strategy import NearestAvailableAgentStrategy
from restaurant_search_strategy import SearchByCityStrategy, SearchByProximityStrategy, SearchByMenuKeywordStrategy
from order_status import OrderStatus
from order_item import OrderItem
from menu_item import MenuItem
from address import Address

class FoodDeliveryServiceDemo:
    @staticmethod
    def main():
        # 1. Setup the system
        service = FoodDeliveryService.get_instance()
        service.set_assignment_strategy(NearestAvailableAgentStrategy())

        # 2. Define Addresses
        alice_address = Address("123 Maple St", "Springfield", "12345", 40.7128, -74.0060)
        pizza_address = Address("456 Oak Ave", "Springfield", "12345", 40.7138, -74.0070)
        burger_address = Address("789 Pine Ln", "Springfield", "12345", 40.7108, -74.0050)
        taco_address = Address("101 Elm Ct", "Shelbyville", "54321", 41.7528, -75.0160)

        # 3. Register entities
        alice = service.register_customer("Alice", "123-4567-890", alice_address)
        pizza_palace = service.register_restaurant("Pizza Palace", pizza_address)
        burger_barn = service.register_restaurant("Burger Barn", burger_address)
        taco_town = service.register_restaurant("Taco Town", taco_address)
        service.register_delivery_agent("Bob", "321-4567-880", Address("1 B", "Springfield", "12345", 40.71, -74.00))

        # 4. Setup menus
        pizza_palace.add_to_menu(MenuItem("P001", "Margherita Pizza", 12.99))
        pizza_palace.add_to_menu(MenuItem("P002", "Veggie Pizza", 11.99))
        burger_barn.add_to_menu(MenuItem("B001", "Classic Burger", 8.99))
        taco_town.add_to_menu(MenuItem("T001", "Crunchy Taco", 3.50))

        # 5. Demonstrate Search Functionality
        print("\n--- 1. Searching for Restaurants ---")

        # (A) Search by City
        print("\n(A) Restaurants in 'Springfield':")
        city_search = [SearchByCityStrategy("Springfield")]
        springfield_restaurants = service.search_restaurants(city_search)
        for r in springfield_restaurants:
            print(f"  - {r.get_name()}")

        # (B) Search for restaurants near Alice
        print("\n(B) Restaurants near Alice (within 0.01 distance units):")
        proximity_search = [SearchByProximityStrategy(alice_address, 0.01)]
        nearby_restaurants = service.search_restaurants(proximity_search)
        for r in nearby_restaurants:
            distance = alice_address.distance_to(r.get_address())
            print(f"  - {r.get_name()} (Distance: {distance:.4f})")

        # (C) Search for restaurants that serve 'Pizza'
        print("\n(C) Restaurants that serve 'Pizza':")
        menu_search = [SearchByMenuKeywordStrategy("Pizza")]
        pizza_restaurants = service.search_restaurants(menu_search)
        for r in pizza_restaurants:
            print(f"  - {r.get_name()}")

        # (D) Combined Search: Find restaurants near Alice that serve 'Burger'
        print("\n(D) Burger joints near Alice:")
        combined_search = [
            SearchByProximityStrategy(alice_address, 0.01),
            SearchByMenuKeywordStrategy("Burger")
        ]
        burger_joints_near_alice = service.search_restaurants(combined_search)
        for r in burger_joints_near_alice:
            print(f"  - {r.get_name()}")

        # 6. Demonstrate Browsing a Menu
        print("\n--- 2. Browsing a Menu ---")
        print("\nMenu for 'Pizza Palace':")
        pizza_menu = service.get_restaurant_menu(pizza_palace.get_id())
        for item in pizza_menu.get_items().values():
            print(f"  - {item.get_name()}: ${item.get_price():.2f}")

        # 7. Alice places an order from a searched restaurant
        print("\n--- 3. Placing an Order ---")
        if pizza_restaurants:
            chosen_restaurant = pizza_restaurants[0]
            chosen_item = chosen_restaurant.get_menu().get_item("P001")

            print(f"\nAlice is ordering '{chosen_item.get_name()}' from '{chosen_restaurant.get_name()}'.")
            order = service.place_order(alice.get_id(), chosen_restaurant.get_id(), [OrderItem(chosen_item, 1)])

            print("\n--- Restaurant starts preparing the order ---")
            service.update_order_status(order.get_id(), OrderStatus.PREPARING)

            print("\n--- Order is ready for pickup ---")
            print("System will now find the nearest available delivery agent...")
            service.update_order_status(order.get_id(), OrderStatus.READY_FOR_PICKUP)

            print("\n--- Agent delivers the order ---")
            service.update_order_status(order.get_id(), OrderStatus.DELIVERED)


if __name__ == "__main__":
    FoodDeliveryServiceDemo.main()