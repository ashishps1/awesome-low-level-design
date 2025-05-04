# Restaurant Management System (LLD)

## Problem Statement

Design and implement a Restaurant Management System that allows customers to make reservations, place orders, manage tables, generate bills, and process payments. The system should also support staff management and menu management.

---

## Requirements

- **Table Management:** The system manages tables, their availability, and assignments.
- **Reservation Management:** Customers can reserve tables in advance.
- **Menu Management:** The system manages a menu of items, including prices and descriptions.
- **Order Placement:** Customers can place orders for menu items.
- **Order Tracking:** The system tracks the status of each order (e.g., PLACED, PREPARING, SERVED, COMPLETED).
- **Billing:** The system generates bills for completed orders.
- **Payment Processing:** The system processes payments for bills.
- **Staff Management:** The system manages staff assignments (e.g., waiters, chefs).
- **Extensibility:** Easy to add new features such as customer feedback, loyalty programs, or online ordering.

---

## Core Entities

- **RestaurantManagementSystem:** Main class that manages tables, reservations, orders, menu, staff, and payments.
- **Table:** Represents a table in the restaurant, with table number, capacity, and availability.
- **Reservation:** Represents a reservation for a table by a customer.
- **MenuItem:** Represents an item on the menu, with name, description, and price.
- **Order:** Represents a customer's order, including items, status, and associated table.
- **OrderItem:** Represents an item in an order.
- **OrderStatus:** Enum for order status (PLACED, PREPARING, SERVED, COMPLETED).
- **Bill:** Represents the bill for an order, including total amount and payment status.
- **Payment (in payment/):** Represents a payment transaction for a bill.
- **Staff:** Represents a staff member (e.g., waiter, chef).

---

## Class Design

### 1. RestaurantManagementSystem
- **Fields:** List<Table> tables, List<Reservation> reservations, List<MenuItem> menu, List<Order> orders, List<Bill> bills, List<Staff> staff, PaymentProcessor paymentProcessor
- **Methods:** addTable(Table), addMenuItem(MenuItem), makeReservation(Reservation), placeOrder(Order), updateOrderStatus(Order, OrderStatus), generateBill(Order), processPayment(Bill, Payment), addStaff(Staff), etc.

### 2. Table
- **Fields:** int tableNumber, int capacity, boolean isAvailable

### 3. Reservation
- **Fields:** int id, Table table, String customerName, Date reservationTime

### 4. MenuItem
- **Fields:** int id, String name, String description, double price

### 5. Order
- **Fields:** int id, Table table, List<OrderItem> items, OrderStatus status

### 6. OrderItem
- **Fields:** MenuItem menuItem, int quantity

### 7. OrderStatus (enum)
- Values: PLACED, PREPARING, SERVED, COMPLETED

### 8. Bill
- **Fields:** int id, Order order, double totalAmount, boolean isPaid

### 9. Payment (in payment/)
- **Fields:** int id, double amount, String method, PaymentStatus status

### 10. Staff
- **Fields:** int id, String name, String role

### 11. PaymentProcessor (in payment/)
- **Methods:** process(Payment), validate(Payment)

---

## Example Usage

```java
RestaurantManagementSystem system = new RestaurantManagementSystem();
Table table = new Table(1, 4, true);
system.addTable(table);

MenuItem pizza = new MenuItem(1, "Pizza", "Cheese Pizza", 12.0);
system.addMenuItem(pizza);

Reservation reservation = new Reservation(1, table, "Alice", new Date());
system.makeReservation(reservation);

Order order = new Order(1, table, List.of(new OrderItem(pizza, 2)), OrderStatus.PLACED);
system.placeOrder(order);

Bill bill = system.generateBill(order);
Payment payment = new Payment(1, bill.getTotalAmount(), "CREDIT_CARD");
system.processPayment(bill, payment);
```

---

## Demo

See `RestaurantManagementSystemDemo.java` for a sample usage and simulation of the restaurant management system.

---

## Extending the Design

- **Add customer feedback:** Allow customers to rate their experience.
- **Add loyalty programs:** Track and reward repeat customers.
- **Add online ordering:** Support for online reservations and orders.

---