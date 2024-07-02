from payment import Payment, PaymentMethod, PaymentStatus
from menu_item import MenuItem
from order import Order, OrderStatus
from reservation import Reservation
from restaurant import Restaurant
from staff import Staff
from datetime import datetime

class RestaurantManagementDemo:
    @staticmethod
    def run():
        restaurant = Restaurant()

        # Add menu items
        restaurant.add_menu_item(MenuItem(1, "Burger", "Delicious burger", 9.99, True))
        restaurant.add_menu_item(MenuItem(2, "Pizza", "Cheesy pizza", 12.99, True))
        restaurant.add_menu_item(MenuItem(3, "Salad", "Fresh salad", 7.99, True))

        # Place an order
        order = Order(1, [MenuItem(1, "Burger", "Delicious burger", 9.99, True),
                        MenuItem(3, "Salad", "Fresh salad", 7.99, True)],
                    17.98, OrderStatus.PENDING, datetime.now())
        restaurant.place_order(order)

        # Make a reservation
        reservation = Reservation(1, "John Doe", "1234567890", 4, datetime.now())
        restaurant.make_reservation(reservation)

        # Process a payment
        payment = Payment(1, 17.98, PaymentMethod.CREDIT_CARD, PaymentStatus.PENDING)
        restaurant.process_payment(payment)

        # Update order status
        restaurant.update_order_status(1, OrderStatus.PREPARING)
        restaurant.update_order_status(1, OrderStatus.READY)
        restaurant.update_order_status(1, OrderStatus.COMPLETED)

        # Add staff
        restaurant.add_staff(Staff(1, "Alice", "Manager", "9876543210"))
        restaurant.add_staff(Staff(2, "Bob", "Chef", "5432109876"))

        # Get menu
        menu = restaurant.get_menu()
        print("Menu:")
        for item in menu:
            print(f"{item.get_name()} - ${item.get_price():.2f}")

if __name__ == "__main__":
    RestaurantManagementDemo.run()