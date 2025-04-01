from online_shopping_service import OnlineShoppingService
from product import Product
from user import User
from shopping_cart import ShoppingCart
from credit_card_payment import CreditCardPayment

class OnlineShoppingServiceDemo:
    def run():
        shopping_service = OnlineShoppingService()

        # Register users
        user1 = User("U001", "John Doe", "john@example.com", "password123")
        user2 = User("U002", "Jane Smith", "jane@example.com", "password456")
        shopping_service.register_user(user1)
        shopping_service.register_user(user2)

        # Add products
        product1 = Product("P001", "Smartphone", "High-end smartphone", 999.99, 10)
        product2 = Product("P002", "Laptop", "Powerful gaming laptop", 1999.99, 5)
        shopping_service.add_product(product1)
        shopping_service.add_product(product2)

        # User 1 adds products to cart and places an order
        cart1 = ShoppingCart()
        cart1.add_item(product1, 2)
        cart1.add_item(product2, 1)
        payment1 = CreditCardPayment()
        order1 = shopping_service.place_order(user1, cart1, payment1)
        print("Order placed:", order1.id)

        # User 2 searches for products and adds to cart
        search_results = shopping_service.search_products("laptop")
        print("Search Results:")
        for product in search_results:
            print(product.name)

        cart2 = ShoppingCart()
        cart2.add_item(search_results[0], 1)
        payment2 = CreditCardPayment()
        order2 = shopping_service.place_order(user2, cart2, payment2)
        print("Order placed:", order2.id)

        # User 1 views order history
        user_orders = user1.orders
        print("User 1 Order History:")
        for order in user_orders:
            print("Order ID:", order.id)
            print("Total Amount: $", order.total_amount)
            print("Status:", order.status)

if __name__ == "__main__":
    OnlineShoppingServiceDemo.run()