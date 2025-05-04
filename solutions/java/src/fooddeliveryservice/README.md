# Food Delivery Service (LLD)

## Problem Statement

Design and implement a Food Delivery Service system that allows customers to place orders from restaurants, manages menu items, assigns delivery agents, and tracks order status from placement to delivery.

---

## Requirements

- **Customer Registration:** Customers can register and place orders.
- **Restaurant Management:** The system manages multiple restaurants, each with its own menu.
- **Menu Management:** Restaurants can add and update menu items.
- **Order Placement:** Customers can place orders for menu items from a restaurantManagementSystem.
- **Order Tracking:** The system tracks the status of each order (e.g., PLACED, PREPARING, OUT_FOR_DELIVERY, DELIVERED).
- **Delivery Assignment:** Orders are assigned to available delivery agents.
- **Delivery Agent Management:** The system manages delivery agents and their availability.
- **Extensibility:** Easy to add new features such as ratings, reviews, or payment integration.

---

## Core Entities

- **FoodDeliveryService:** Main class that manages customers, restaurants, orders, and delivery agents.
- **Customer:** Represents a customer who can place orders.
- **Restaurant:** Represents a restaurantManagementSystem with a menu of items.
- **MenuItem:** Represents an item on a restaurantManagementSystem's menu.
- **Order:** Represents a customer's order, including items, status, and assigned delivery agent.
- **DeliveryAgent:** Represents a delivery agent who delivers orders.

---

## Class Design

### 1. FoodDeliveryService
- **Fields:** List<Customer> customers, List<Restaurant> restaurants, List<DeliveryAgent> agents, List<Order> orders
- **Methods:** registerCustomer(Customer), addRestaurant(Restaurant), addMenuItem(Restaurant, MenuItem), placeOrder(Customer, Restaurant, List<MenuItem>), assignDeliveryAgent(Order), updateOrderStatus(Order, Status), etc.

### 2. Customer
- **Fields:** int id, String name, List<Order> orders

### 3. Restaurant
- **Fields:** int id, String name, List<MenuItem> menu

### 4. MenuItem
- **Fields:** int id, String name, double price

### 5. Order
- **Fields:** int id, Customer customer, Restaurant restaurantManagementSystem, List<MenuItem> items, OrderStatus status, DeliveryAgent agent

### 6. DeliveryAgent
- **Fields:** int id, String name, boolean available, List<Order> assignedOrders

---

## Example Usage

```java
FoodDeliveryService service = new FoodDeliveryService();
Customer alice = new Customer(1, "Alice");
Restaurant pizzaPlace = new Restaurant(1, "Pizza Place");
MenuItem pizza = new MenuItem(1, "Margherita Pizza", 10.0);

service.registerCustomer(alice);
service.addRestaurant(pizzaPlace);
service.addMenuItem(pizzaPlace, pizza);

service.placeOrder(alice, pizzaPlace, List.of(pizza));
```

---

## Demo

See `FoodDeliveryServiceDemo.java` for a sample usage and simulation of the food delivery service.

---

## Extending the Framework

- **Add ratings and reviews:** Allow customers to rate restaurants and delivery agents.
- **Add payment integration:** Support online payments.
- **Add order cancellation or modification:** Allow customers to cancel or modify orders before delivery.

---