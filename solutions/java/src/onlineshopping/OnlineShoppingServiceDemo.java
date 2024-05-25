package onlineshopping;

import onlineshopping.payment.CreditCardPayment;
import onlineshopping.payment.Payment;

import java.util.List;

public class OnlineShoppingServiceDemo {
    public static void run() {
        OnlineShoppingService shoppingService = OnlineShoppingService.getInstance();

        // Register users
        User user1 = new User("U001", "John Doe", "john@example.com", "password123");
        User user2 = new User("U002", "Jane Smith", "jane@example.com", "password456");
        shoppingService.registerUser(user1);
        shoppingService.registerUser(user2);

        // Add products
        Product product1 = new Product("P001", "Smartphone", "High-end smartphone", 999.99, 10);
        Product product2 = new Product("P002", "Laptop", "Powerful gaming laptop", 1999.99, 5);
        shoppingService.addProduct(product1);
        shoppingService.addProduct(product2);

        // User 1 adds products to cart and places an order
        ShoppingCart cart1 = new ShoppingCart();
        cart1.addItem(product1, 2);
        cart1.addItem(product2, 1);
        Payment payment1 = new CreditCardPayment();
        Order order1 = shoppingService.placeOrder(user1, cart1, payment1);
        System.out.println("Order placed: " + order1.getId());

        // User 2 searches for products and adds to cart
        List<Product> searchResults = shoppingService.searchProducts("laptop");
        System.out.println("Search Results:");
        for (Product product : searchResults) {
            System.out.println(product.getName());
        }

        ShoppingCart cart2 = new ShoppingCart();
        cart2.addItem(searchResults.get(0), 1);
        Payment payment2 = new CreditCardPayment();
        Order order2 = shoppingService.placeOrder(user2, cart2, payment2);
        System.out.println("Order placed: " + order2.getId());

        // User 1 views order history
        List<Order> userOrders = user1.getOrders();
        System.out.println("User 1 Order History:");
        for (Order order : userOrders) {
            System.out.println("Order ID: " + order.getId());
            System.out.println("Total Amount: $" + order.getTotalAmount());
            System.out.println("Status: " + order.getStatus());
        }
    }
}
