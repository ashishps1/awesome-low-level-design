# Online Shopping Service (LLD)

## Problem Statement

Design and implement an Online Shopping Service that allows users to browse products, add items to a cart, place orders, make payments, and track order status.

---

## Requirements

- **User Management:** Users can register, log in, and manage their profiles.
- **Product Catalog:** The system manages a catalog of products with details and prices.
- **Cart Management:** Users can add, update, or remove products in their shopping cart.
- **Order Placement:** Users can place orders for products in their cart.
- **Order Tracking:** The system tracks the status of each order (e.g., PLACED, SHIPPED, DELIVERED, CANCELLED).
- **Payment Processing:** Users can pay for their orders using different payment methods.
- **Extensibility:** Easy to add new features such as discounts, reviews, or wishlists.

---

## Core Entities

- **OnlineShoppingService:** Main class that manages users, products, carts, orders, and payments.
- **User:** Represents a user with a unique ID, name, and cart.
- **Product:** Represents a product with ID, name, description, and price.
- **Cart:** Represents a user's shopping cart containing order items.
- **Order:** Represents an order placed by a user, including items, status, and payment.
- **OrderItem:** Represents an item in an order or cart.
- **OrderStatus:** Enum for order status (PLACED, SHIPPED, DELIVERED, CANCELLED).
- **Payment (in payment/):** Represents a payment transaction for an order.
- **PaymentProcessor (in payment/):** Handles payment logic and validation.

---

## Class Design

### 1. OnlineShoppingService
- **Fields:** List<User> users, List<Product> products, List<Order> orders, PaymentProcessor paymentProcessor
- **Methods:** registerUser(User), addProduct(Product), addToCart(User, Product, int quantity), placeOrder(User), processPayment(Order, Payment), updateOrderStatus(Order, OrderStatus), etc.

### 2. User
- **Fields:** int id, String name, Cart cart

### 3. Product
- **Fields:** int id, String name, String description, double price

### 4. Cart
- **Fields:** List<OrderItem> items
- **Methods:** addItem(Product, int quantity), removeItem(Product), updateQuantity(Product, int quantity), getItems()

### 5. Order
- **Fields:** int id, User user, List<OrderItem> items, OrderStatus status, Payment payment

### 6. OrderItem
- **Fields:** Product product, int quantity

### 7. OrderStatus (enum)
- Values: PLACED, SHIPPED, DELIVERED, CANCELLED

### 8. Payment (in payment/)
- **Fields:** int id, double amount, String method, PaymentStatus status

### 9. PaymentProcessor (in payment/)
- **Methods:** process(Payment), validate(Payment)

---

## Example Usage

```java
OnlineShoppingService service = new OnlineShoppingService();
User alice = new User(1, "Alice");
Product phone = new Product(1, "Smartphone", "Latest model", 699.0);

service.registerUser(alice);
service.addProduct(phone);
service.addToCart(alice, phone, 1);

Order order = service.placeOrder(alice);
Payment payment = new Payment(1, 699.0, "CREDIT_CARD");
service.processPayment(order, payment);
```

---

## Demo

See `OnlineShoppingServiceDemo.java` for a sample usage and simulation of the online shopping service.

---

## Extending the Framework

- **Add discounts or coupons:** Support promotional pricing.
- **Add product reviews:** Allow users to review and rate products.
- **Add wishlists:** Allow users to save products for later.

---