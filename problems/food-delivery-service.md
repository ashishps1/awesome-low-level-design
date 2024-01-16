# Designing an Online Food Delivery Service Like Swiggy

In this article, we explore the object-oriented design and implementation of an Online Food Delivery Service similar to Swiggy using Java. 

This system encompasses functionalities essential for online food ordering and delivery.

## System Requirements

The Online Food Delivery System should:

1. **Restaurant Management**: Manage restaurant profiles, menus, and availability.
2. **User Account Management**: Handle customer and delivery agent profiles.
3. **Order Processing**: Enable customers to place orders and track their status.
4. **Delivery Management**: Assign orders to delivery agents and manage the delivery process.
5. **Payment Processing**: Handle various modes of payment.

## Core Use Cases

1. **Adding and Managing Restaurants**
2. **Registering and Managing User and Delivery Agent Accounts**
3. **Placing and Tracking Orders**
4. **Assigning and Managing Deliveries**
5. **Processing Payments**

## UML/Class Diagrams

Key Classes:

- `OnlineFoodDeliveryService`: Manages the overall system.
- `User`: Represents a customer.
- `Restaurant`: Manages a restaurant's profile and menu.
- `Order`: Represents a food order.
- `DeliveryAgent`: Manages a delivery agent's information.
- `Payment`: Handles payment transactions.

## Java Implementation

### Restaurant Class

Manages restaurant information and menus.

```java
import java.util.HashMap;
import java.util.Map;

public class Restaurant {
    private String restaurantId;
    private String name;
    private Map<String, Double> menu; // Menu items and prices

    public Restaurant(String restaurantId, String name) {
        this.restaurantId = restaurantId;
        this.name = name;
        this.menu = new HashMap<>();
    }

    public void addItemToMenu(String itemName, double price) {
        menu.put(itemName, price);
    }

    // Getters and setters...
}
```
### User Class
Manages customer account information.
```java
public class User {
    private String userId;
    private String name;
    private String address;

    public User(String userId, String name, String address) {
        this.userId = userId;
        this.name = name;
        this.address = address;
    }

    // Getters and setters...
}
```
### Order Class
Represents a customer's food order.
```java
import java.util.Date;
import java.util.Map;

public class Order {
    private String orderId;
    private User user;
    private Restaurant restaurant;
    private Map<String, Integer> orderedItems; // Item names and quantities
    private Date orderTime;
    private OrderStatus status;

    public Order(String orderId, User user, Restaurant restaurant, Map<String, Integer> orderedItems, Date orderTime) {
        this.orderId = orderId;
        this.user = user;
        this.restaurant = restaurant;
        this.orderedItems = orderedItems;
        this.orderTime = orderTime;
        this.status = OrderStatus.PLACED;
    }

    public void updateStatus(OrderStatus newStatus) {
        this.status = newStatus;
    }

    // Getters and setters...
}

enum OrderStatus {
    PLACED, PREPARING, OUT_FOR_DELIVERY, DELIVERED, CANCELLED
}
```
### DeliveryAgent Class
Manages delivery agent information.
```java
public class DeliveryAgent {
    private String agentId;
    private String name;
    private boolean isAvailable;

    public DeliveryAgent(String agentId, String name) {
        this.agentId = agentId;
        this.name = name;
        this.isAvailable = true;
    }

    public void setAvailability(boolean isAvailable) {
        this.isAvailable = isAvailable;
    }

    // Getters and setters...
}
```
### Payment Class
Handles payment transactions.
```java
public class Payment {
    private String paymentId;
    private double amount;
    private PaymentStatus status;

    public Payment(String paymentId, double amount) {
        this.paymentId = paymentId;
        this.amount = amount;
        this.status = PaymentStatus.PENDING;
    }

    public void completePayment() {
        this.status = PaymentStatus.COMPLETED;
    }

    // Getters and setters...
}

enum PaymentStatus {
    PENDING, COMPLETED, FAILED
}
```
### OnlineFoodDeliveryService Class
Manages the online food delivery service operations.
```java
import java.util.ArrayList;
import java.util.List;

public class OnlineFoodDeliveryService {
    private List<User> users;
    private List<Restaurant> restaurants;
    private List<Order> orders;
    private List<DeliveryAgent> deliveryAgents;

    public OnlineFoodDeliveryService() {
        this.users = new ArrayList<>();
        this.restaurants = new ArrayList<>();
        this.orders = new ArrayList<>();
        this.deliveryAgents = new ArrayList<>();
    }

    public void addUser(User user) {
        users.add(user);
    }

    public void addRestaurant(Restaurant restaurant) {
        restaurants.add(restaurant);
    }

    public void addOrder(Order order) {
        orders.add(order);
    }

    public void assignDeliveryAgent(String orderId, String agentId) {
        Order order = findOrderById(orderId);
        DeliveryAgent agent = findAgentById(agentId);

        if (order != null && agent != null && agent.isAvailable()) {
            // Assign order to agent and update status
            agent.setAvailability(false);
            order.updateStatus(OrderStatus.OUT_FOR_DELIVERY);
        }
    }

    private Order findOrderById(String orderId) {
        for (Order order : orders) {
            if (order.getOrderId().equals(orderId)) {
                return order;
            }
        }
        return null;
    }

    private DeliveryAgent findAgentById(String agentId) {
        for (DeliveryAgent agent : deliveryAgents) {
            if (agent.getAgentId().equals(agentId)) {
                return agent;
            }
        }
        return null;
    }

    // Other necessary methods...
}
```