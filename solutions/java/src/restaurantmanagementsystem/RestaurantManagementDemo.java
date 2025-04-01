package restaurantmanagementsystem;

import restaurantmanagementsystem.payment.Payment;
import restaurantmanagementsystem.payment.PaymentMethod;
import restaurantmanagementsystem.payment.PaymentStatus;

import java.sql.Timestamp;
import java.util.Arrays;
import java.util.List;

public class RestaurantManagementDemo {
    public static void run() {
        Restaurant restaurant = Restaurant.getInstance();

        // Add menu items
        restaurant.addMenuItem(new MenuItem(1, "Burger", "Delicious burger", 9.99, true));
        restaurant.addMenuItem(new MenuItem(2, "Pizza", "Cheesy pizza", 12.99, true));
        restaurant.addMenuItem(new MenuItem(3, "Salad", "Fresh salad", 7.99, true));

        // Place an order
        Order order = new Order(1, Arrays.asList(new MenuItem(1, "Burger", "Delicious burger", 9.99, true),
                new MenuItem(3, "Salad", "Fresh salad", 7.99, true)), 17.98, OrderStatus.PENDING, new Timestamp(System.currentTimeMillis()));
        restaurant.placeOrder(order);

        // Make a reservation
        Reservation reservation = new Reservation(1, "John Doe", "1234567890", 4, new Timestamp(System.currentTimeMillis()));
        restaurant.makeReservation(reservation);

        // Process a payment
        Payment payment = new Payment(1, 17.98, PaymentMethod.CREDIT_CARD, PaymentStatus.PENDING);
        restaurant.processPayment(payment);

        // Update order status
        restaurant.updateOrderStatus(1, OrderStatus.PREPARING);
        restaurant.updateOrderStatus(1, OrderStatus.READY);
        restaurant.updateOrderStatus(1, OrderStatus.COMPLETED);

        // Add staff
        restaurant.addStaff(new Staff(1, "Alice", "Manager", "9876543210"));
        restaurant.addStaff(new Staff(2, "Bob", "Chef", "5432109876"));

        // Get menu
        List<MenuItem> menu = restaurant.getMenu();
        System.out.println("Menu:");
        for (MenuItem item : menu) {
            System.out.println(item.getName() + " - $" + item.getPrice());
        }
    }
}
