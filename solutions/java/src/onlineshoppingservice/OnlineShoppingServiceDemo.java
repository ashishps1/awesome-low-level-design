package onlineshoppingservice;

import java.util.List;

import onlineshoppingservice.payment.CreditCardPayment;

public class OnlineShoppingServiceDemo {
    public static void run() {
        OnlineShoppingService shoppingService = OnlineShoppingService.getInstance();

        // Register users
        User user1 = shoppingService.registerUser("John Doe", "john@example.com", "password123");
        User user2 = shoppingService.registerUser("Jane Smith", "jane@example.com", "password456");

        // Add products
        Product product1 = shoppingService.addProduct("Smartphone", "High-end smartphone", 999.99, 10);
        Product product2 = shoppingService.addProduct("Laptop", "Powerful gaming laptop", 1999.99, 5);

        // Add items to users cart
        shoppingService.addToCart(user1.getId(), product1.getId(), 2);
        shoppingService.addToCart(user1.getId(), product2.getId(), 1);

        // Place order
        Order order1 = shoppingService.placeOrder(user1.getId(), new CreditCardPayment());
        System.out.println("Order placed: " + order1.getId());

        // User searches for products
        List<Product> searchResults = shoppingService.searchProducts("laptop");
        System.out.println("Search Results:");
        for (Product product : searchResults) {
            System.out.println(product.getName());
        }

        // User views order history
        List<Order> userOrders = user1.getOrders();
        System.out.println("User 1 Order History:");
        for (Order order : userOrders) {
            System.out.println("Order ID: " + order.getId());
            System.out.println("Total Amount: $" + order.getTotalAmount());
            System.out.println("Status: " + order.getStatus());
        }
    }
}
