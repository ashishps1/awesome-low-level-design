# Designing an Online Shopping System Like Amazon

In this blog post, we're going to design and implement an Online Shopping System resembling Amazon, using Java. 

This system will cover product listings, user accounts, shopping carts, and order processing.

## System Requirements

The Online Shopping System should:

1. **Product Management:** Manage a catalog of products.
2. **User Account Management:** Handle user registrations and logins.
3. **Shopping Cart Management:** Allow users to add and remove products from their shopping cart.
4. **Order Processing:** Process user orders and maintain order history.

## Core Use Cases

1. **Browsing Products**
2. **Managing User Accounts**
3. **Handling Shopping Carts**
4. **Processing Orders**

## UML/Class Diagrams

Key Classes:

- `OnlineShoppingSystem`: Manages the overall system.
- `Product`: Represents a product in the catalog.
- `User`: Represents a user of the system.
- `ShoppingCart`: Manages the shopping cart.
- `Order`: Represents a user's order.

## Java Implementation

### Product Class

Represents a product in the store.

```java
public class Product {
    private String productId;
    private String name;
    private double price;
    private String description;

    public Product(String productId, String name, double price, String description) {
        this.productId = productId;
        this.name = name;
        this.price = price;
        this.description = description;
    }

    // Getters and setters...
}
```
### User Class
Handles user account information.
```java
public class User {
    private String userId;
    private String name;
    private String email;
    private ShoppingCart cart;
    private List<Order> orderHistory;

    public User(String userId, String name, String email) {
        this.userId = userId;
        this.name = name;
        this.email = email;
        this.cart = new ShoppingCart(this);
        this.orderHistory = new ArrayList<>();
    }

    public void addProductToCart(Product product, int quantity) {
        cart.addProduct(product, quantity);
    }

    public Order checkout() {
        Order order = cart.checkout();
        orderHistory.add(order);
        return order;
    }

    // Getters and setters...
}
```
### ShoppingCart Class
Manages shopping cart operations.
```java
import java.util.HashMap;
import java.util.Map;

public class ShoppingCart {
    private User owner;
    private Map<Product, Integer> items;

    public ShoppingCart(User owner) {
        this.owner = owner;
        this.items = new HashMap<>();
    }

    public void addProduct(Product product, int quantity) {
        items.put(product, items.getOrDefault(product, 0) + quantity);
    }

    public Order checkout() {
        Order newOrder = new Order(this.owner, new HashMap<>(items));
        items.clear();
        return newOrder;
    }

    // Getters and setters...
}
```
### Order Class
Represents a user's order.
```java
import java.util.Map;

public class Order {
    private User user;
    private Map<Product, Integer> orderedItems;
    private OrderStatus status;

    public Order(User user, Map<Product, Integer> orderedItems) {
        this.user = user;
        this.orderedItems = orderedItems;
        this.status = OrderStatus.PROCESSING;
    }

    public void updateStatus(OrderStatus newStatus) {
        this.status = newStatus;
    }

    // Getters and setters...
}

enum OrderStatus {
    PROCESSING, SHIPPED, DELIVERED
}
```
### OnlineShoppingSystem Class
Main class for managing the online shopping platform.
```java
import java.util.ArrayList;
import java.util.List;

public class OnlineShoppingSystem {
    private List<Product> catalog;
    private List<User> users;

    public OnlineShoppingSystem() {
        this.catalog = new ArrayList<>();
        this.users = new ArrayList<>();
    }

    public void addProductToCatalog(Product product) {
        catalog.add(product);
    }

    public void addUser(User user) {
        users.add(user);
    }

    // Other necessary methods...
}
```