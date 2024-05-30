package fooddeliveryservice;

import fooddeliveryservice.order.Order;
import fooddeliveryservice.order.OrderItem;
import fooddeliveryservice.order.OrderStatus;

import java.util.ArrayList;
import java.util.List;

public class FoodDeliveryServiceDemo {
    public static void run() {
        FoodDeliveryService deliveryService = FoodDeliveryService.getInstance();

        // Register customers
        Customer customer1 = new Customer("C001", "John Doe", "john@example.com", "1234567890");
        Customer customer2 = new Customer("C002", "Jane Smith", "jane@example.com", "9876543210");
        deliveryService.registerCustomer(customer1);
        deliveryService.registerCustomer(customer2);

        // Register restaurants
        List<MenuItem> restaurant1Menu = new ArrayList<>();
        restaurant1Menu.add(new MenuItem("M001", "Burger", "Delicious burger", 9.99));
        restaurant1Menu.add(new MenuItem("M002", "Pizza", "Cheesy pizza", 12.99));
        Restaurant restaurant1 = new Restaurant("R001", "Restaurant 1", "Address 1", restaurant1Menu);
        deliveryService.registerRestaurant(restaurant1);

        List<MenuItem> restaurant2Menu = new ArrayList<>();
        restaurant2Menu.add(new MenuItem("M003", "Sushi", "Fresh sushi", 15.99));
        restaurant2Menu.add(new MenuItem("M004", "Ramen", "Delicious ramen", 10.99));
        Restaurant restaurant2 = new Restaurant("R002", "Restaurant 2", "Address 2", restaurant2Menu);
        deliveryService.registerRestaurant(restaurant2);

        // Register delivery agents
        DeliveryAgent agent1 = new DeliveryAgent("D001", "Agent 1", "9999999999");
        DeliveryAgent agent2 = new DeliveryAgent("D002", "Agent 2", "8888888888");
        deliveryService.registerDeliveryAgent(agent1);
        deliveryService.registerDeliveryAgent(agent2);

        // Place an order
        List<OrderItem> orderItems = new ArrayList<>();
        orderItems.add(new OrderItem(restaurant1Menu.get(0), 2));
        orderItems.add(new OrderItem(restaurant1Menu.get(1), 1));
        Order order = deliveryService.placeOrder(customer1.getId(), restaurant1.getId(), orderItems);

        // Update order status
        deliveryService.updateOrderStatus(order.getId(), OrderStatus.CONFIRMED);
        System.out.println("Order status updated: " + order.getStatus());

        // Cancel an order
        Order order2 = deliveryService.placeOrder(customer2.getId(), restaurant2.getId(), List.of(new OrderItem(restaurant2Menu.get(0), 1)));
        deliveryService.cancelOrder(order2.getId());
    }
}
