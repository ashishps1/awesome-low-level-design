package onlineshoppingservice;

import onlineshoppingservice.decorator.GiftWrapDecorator;
import onlineshoppingservice.enums.ProductCategory;
import onlineshoppingservice.models.*;
import onlineshoppingservice.strategy.CreditCardPaymentStrategy;
import onlineshoppingservice.strategy.UPIPaymentStrategy;

public class OnlineShoppingDemo {
    public static void main(String[] args) {
        // --- System Setup (Singleton and Services) ---
        OnlineShoppingSystem system = OnlineShoppingSystem.getInstance();

        // --- Create and Add Products to Catalog (Builder Pattern) ---
        Product laptop = new Product.Builder("Dell XPS 15", 1499.99)
                .withDescription("A powerful and sleek laptop.")
                .withCategory(ProductCategory.ELECTRONICS)
                .build();
        Product book = new Product.Builder("The Pragmatic Programmer", 45.50)
                .withDescription("A classic book for software developers.")
                .withCategory(ProductCategory.BOOKS)
                .build();

        system.addProduct(laptop, 10); // 10 laptops in stock
        system.addProduct(book, 50);   // 50 books in stock

        // --- Register a Customer ---
        Address aliceAddress = new Address("123 Main St", "Anytown", "CA", "12345");
        Customer alice = system.registerCustomer("Alice", "alice@example.com", "password123", aliceAddress);

        // --- Alice Shops ---
        System.out.println("--- Alice starts shopping ---");

        // Alice adds a laptop to her cart
        system.addToCart(alice.getId(), laptop.getId(), 1);
        System.out.println("Alice added a laptop to her cart.");

        // Alice decides to gift-wrap the book (Decorator Pattern)
        Product giftWrappedBook = new GiftWrapDecorator(book);
        system.addToCart(alice.getId(), giftWrappedBook.getId(), 1);
        System.out.printf("Alice added a gift-wrapped book. Original price: $%.2f, New price: $%.2f%n",
                book.getPrice(), giftWrappedBook.getPrice());

        ShoppingCart aliceCart = system.getCustomerCart(alice.getId());
        System.out.printf("Alice's cart total: $%.2f%n", aliceCart.calculateTotal());

        // --- Alice Checks Out ---
        System.out.println("\n--- Alice proceeds to checkout ---");
        Order aliceOrder = system.placeOrder(alice.getId(), new CreditCardPaymentStrategy("1234-5678-9876-5432"));
        if (aliceOrder == null) {
            System.out.println("Order placement failed.");
            return;
        }

        System.out.printf("Order #%s placed successfully for Alice.%n", aliceOrder.getId());

        // --- Order State and Notifications (State, Observer Patterns) ---
        System.out.println("\n--- Order processing starts ---");

        // The warehouse ships the order
        aliceOrder.shipOrder(); // This will trigger a notification to Alice

        // The delivery service marks the order as delivered
        aliceOrder.deliverOrder(); // This will also trigger a notification

        // Try to cancel a delivered order (State pattern prevents this)
        aliceOrder.cancelOrder();

        System.out.println("\n--- Out of Stock Scenario ---");
        Customer bob = system.registerCustomer("Bob", "bob@example.com", "pass123", aliceAddress);

        // Bob tries to buy 15 laptops, but only 9 are left (1 was bought by Alice)
        system.addToCart(bob.getId(), laptop.getId(), 15);

        Order bobOrder = system.placeOrder(bob.getId(), new UPIPaymentStrategy("testupi@hdfc"));
        if (bobOrder == null) {
            System.out.println("Bob's order was correctly prevented due to insufficient stock.");
        }
    }
}
