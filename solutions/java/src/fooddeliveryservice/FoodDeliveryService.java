package fooddeliveryservice;

import fooddeliveryservice.entity.*;
import fooddeliveryservice.order.Order;
import fooddeliveryservice.order.OrderItem;
import fooddeliveryservice.order.OrderStatus;
import fooddeliveryservice.search.RestaurantSearchStrategy;
import fooddeliveryservice.strategy.DeliveryAssignmentStrategy;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.concurrent.ConcurrentHashMap;

public class FoodDeliveryService {
    private static volatile FoodDeliveryService instance;
    private final Map<String, Customer> customers = new ConcurrentHashMap<>();
    private final Map<String, Restaurant> restaurants = new ConcurrentHashMap<>();
    private final Map<String, DeliveryAgent> deliveryAgents = new ConcurrentHashMap<>();
    private final Map<String, Order> orders = new ConcurrentHashMap<>();
    private DeliveryAssignmentStrategy assignmentStrategy;

    private FoodDeliveryService() {}

    public static FoodDeliveryService getInstance() {
        if (instance == null) {
            synchronized (FoodDeliveryService.class) {
                if (instance == null) instance = new FoodDeliveryService();
            }
        }
        return instance;
    }

    public void setAssignmentStrategy(DeliveryAssignmentStrategy assignmentStrategy) {
        this.assignmentStrategy = assignmentStrategy;
    }

    // --- Registration ---
    public Customer registerCustomer(String name, String phone, Address address) {
        Customer customer = new Customer(name, phone, address);
        customers.put(customer.getId(), customer);
        return customer;
    }

    public Restaurant registerRestaurant(String name, Address address) {
        Restaurant restaurant = new Restaurant(name, address);
        restaurants.put(restaurant.getId(), restaurant);
        return restaurant;
    }

    public DeliveryAgent registerDeliveryAgent(String name, String phone, Address initialLocation) {
        DeliveryAgent deliveryAgent = new DeliveryAgent(name, phone, initialLocation);
        deliveryAgents.put(deliveryAgent.getId(), deliveryAgent);
        return deliveryAgent;
    }

    public Order placeOrder(String customerId, String restaurantId, List<OrderItem> items) {
        Customer customer = customers.get(customerId);
        Restaurant restaurant = restaurants.get(restaurantId);
        if (customer == null || restaurant == null) throw new NoSuchElementException("Customer or Restaurant not found.");

        Order order = new Order(customer, restaurant, items);
        orders.put(order.getId(), order);
        customer.addOrderToHistory(order);
        System.out.printf("Order %s placed by %s at %s.\n", order.getId(), customer.getName(), restaurant.getName());
        // Initial PENDING status is set in constructor and observers are notified.
        order.setStatus(OrderStatus.PENDING);
        return order;
    }

    public void updateOrderStatus(String orderId, OrderStatus newStatus) {
        Order order = orders.get(orderId);
        if (order == null)
            throw new NoSuchElementException("Order not found.");

        order.setStatus(newStatus);

        // If order is ready, find a delivery agent.
        if (newStatus == OrderStatus.READY_FOR_PICKUP) {
            assignDelivery(order);
        }
    }

    public void cancelOrder(String orderId) {
        Order order = orders.get(orderId);
        if (order == null) {
            System.out.println("ERROR: Order with ID " + orderId + " not found.");
            return;
        }

        // Delegate the cancellation logic to the Order object itself.
        if (order.cancel()) {
            System.out.println("SUCCESS: Order " + orderId + " has been successfully canceled.");
        } else {
            System.out.println("FAILED: Order " + orderId + " could not be canceled. Its status is: " + order.getStatus());
        }
    }

    private void assignDelivery(Order order) {
        List<DeliveryAgent> availableAgents = new ArrayList<>(deliveryAgents.values());

        assignmentStrategy.findAgent(order, availableAgents).ifPresentOrElse(
                agent -> {
                    order.assignDeliveryAgent(agent);
                    System.out.printf("Agent %s (dist: %.2f) assigned to order %s.\n",
                            agent.getName(),
                            agent.getCurrentLocation().distanceTo(order.getRestaurant().getAddress()),
                            order.getId());
                    order.setStatus(OrderStatus.OUT_FOR_DELIVERY);
                },
                () -> System.out.println("No available delivery agents found for order " + order.getId())
        );
    }

    public List<Restaurant> searchRestaurants(List<RestaurantSearchStrategy> strategies) {
        // Start with the full list of restaurants
        List<Restaurant> results = new ArrayList<>(restaurants.values());

        // Sequentially apply each filter strategy
        // We can also use chain of responsibility design pattern here
        for (RestaurantSearchStrategy strategy : strategies) {
            results = strategy.filter(results);
        }

        return results;
    }

    public Menu getRestaurantMenu(String restaurantId) {
        Restaurant restaurant = restaurants.get(restaurantId);
        if (restaurant == null) {
            throw new NoSuchElementException("Restaurant with ID " + restaurantId + " not found.");
        }
        return restaurant.getMenu();
    }
}
