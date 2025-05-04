package restaurantmanagementsystem;

import restaurantmanagementsystem.payment.CreditCardPayment;

import java.sql.Timestamp;
import java.util.List;

public class RestaurantManagementSystemDemo {
    public static void run() {
        RestaurantManagementSystem restaurantManagementSystem = RestaurantManagementSystem.getInstance();

        // Add menu items
        MenuItem menuItem1 = restaurantManagementSystem.addMenuItem("Burger", 9.99);
        MenuItem menuItem2 = restaurantManagementSystem.addMenuItem("Pizza", 12.99);
        MenuItem menuItem3 = restaurantManagementSystem.addMenuItem("Salad", 7.99);

        // Place an order
        Order order = restaurantManagementSystem.placeOrder(1, List.of(
                new OrderItem(menuItem1, 1),
                new OrderItem(menuItem3, 2)
        ));

        // Update order status
        restaurantManagementSystem.markOrderPreparing(order.getId());
        restaurantManagementSystem.markOrderReady(order.getId());
        restaurantManagementSystem.markOrderServed(order.getId());

        // Process payment
        Bill bill = restaurantManagementSystem.getBill(order.getId());
        restaurantManagementSystem.makePayment(bill, new CreditCardPayment());

        // Make a reservation
        Reservation reservation = restaurantManagementSystem.makeReservation("John Doe", "1234567890", 4, new Timestamp(System.currentTimeMillis()));

        // Add staff
        restaurantManagementSystem.addStaff(new Staff(1, "Alice", "Manager", "9876543210"));
        restaurantManagementSystem.addStaff(new Staff(2, "Bob", "Chef", "5432109876"));

        // Get menu
        List<MenuItem> menu = restaurantManagementSystem.getMenu();
        System.out.println("Menu:");
        for (MenuItem item : menu) {
            System.out.println(item.getName() + " - $" + item.getPrice());
        }
    }
}
