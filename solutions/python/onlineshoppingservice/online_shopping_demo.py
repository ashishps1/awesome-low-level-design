from online_shopping_system import OnlineShoppingSystem
from product import Product
from product_decorators import GiftWrapDecorator
from enums import ProductCategory
from address import Address
from payment_strategy import CreditCardPaymentStrategy, UPIPaymentStrategy

class OnlineShoppingDemo:
    @staticmethod
    def main():
        # System Setup (Singleton and Services)
        system = OnlineShoppingSystem.get_instance()

        # Create and Add Products to Catalog (Builder Pattern)
        laptop = Product.Builder("Dell XPS 15", 1499.99) \
            .with_description("A powerful and sleek laptop.") \
            .with_category(ProductCategory.ELECTRONICS) \
            .build()
        
        book = Product.Builder("The Pragmatic Programmer", 45.50) \
            .with_description("A classic book for software developers.") \
            .with_category(ProductCategory.BOOKS) \
            .build()

        system.add_product(laptop, 10)  # 10 laptops in stock
        system.add_product(book, 50)    # 50 books in stock

        # Register a Customer
        alice_address = Address("123 Main St", "Anytown", "CA", "12345")
        alice = system.register_customer("Alice", "alice@example.com", "password123", alice_address)

        # Alice Shops
        print("--- Alice starts shopping ---")

        # Alice adds a laptop to her cart
        system.add_to_cart(alice.get_id(), laptop.get_id(), 1)
        print("Alice added a laptop to her cart.")

        # Alice decides to gift-wrap the book (Decorator Pattern)
        gift_wrapped_book = GiftWrapDecorator(book)
        system.add_to_cart(alice.get_id(), gift_wrapped_book.get_id(), 1)
        print(f"Alice added a gift-wrapped book. Original price: ${book.get_price():.2f}, New price: ${gift_wrapped_book.get_price():.2f}")

        alice_cart = system.get_customer_cart(alice.get_id())
        print(f"Alice's cart total: ${alice_cart.calculate_total():.2f}")

        # Alice Checks Out
        print("\n--- Alice proceeds to checkout ---")
        alice_order = system.place_order(alice.get_id(), CreditCardPaymentStrategy("1234-5678-9876-5432"))
        if alice_order is None:
            print("Order placement failed.")
            return

        print(f"Order #{alice_order.get_id()} placed successfully for Alice.")

        # Order State and Notifications (State, Observer Patterns)
        print("\n--- Order processing starts ---")

        # The warehouse ships the order
        alice_order.ship_order()  # This will trigger a notification to Alice

        # The delivery service marks the order as delivered
        alice_order.deliver_order()  # This will also trigger a notification

        # Try to cancel a delivered order (State pattern prevents this)
        alice_order.cancel_order()

        print("\n--- Out of Stock Scenario ---")
        bob = system.register_customer("Bob", "bob@example.com", "pass123", alice_address)

        # Bob tries to buy 15 laptops, but only 9 are left (1 was bought by Alice)
        system.add_to_cart(bob.get_id(), laptop.get_id(), 15)

        bob_order = system.place_order(bob.get_id(), UPIPaymentStrategy("testupi@hdfc"))
        if bob_order is None:
            print("Bob's order was correctly prevented due to insufficient stock.")


if __name__ == "__main__":
    OnlineShoppingDemo.main()