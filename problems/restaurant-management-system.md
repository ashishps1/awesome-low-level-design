# Designing an Online Shopping System Like Amazon

In this article, we will explore the object-oriented design and implementation of a Restaurant Management System using Java. 

This system will handle various aspects such as table reservations, order processing, and kitchen management.

## System Requirements

The Online Shopping System should:

1. **Table Reservation Management:** Handle booking and management of tables.
2. **Order Management:** Process food orders from customers.
3. **Inventory Management:** Keep track of kitchen inventory and supplies.
4. **Billing System:** Generate and manage customer bills.

## Core Use Cases

1. **Reserving Tables**
2. **Placing and Processing Food Orders**
3. **Managing Inventory**
4. **Generating and Processing Bills**

## Key Classes:
- `RestaurantManagementSystem`: Manages the entire system.
- `Table`: Represents a dining table in the restaurant.
- `Order`: Manages a customer's food order.
- `Inventory`: Keeps track of kitchen inventory.
- `Bill`: Represents a customer's bill.

## Java Implementation

### Table Class
Represents a dining table in the restaurant.
```java
public class Table {
    private int tableId;
    private int seatingCapacity;
    private boolean isReserved;

    public Table(int tableId, int seatingCapacity) {
        this.tableId = tableId;
        this.seatingCapacity = seatingCapacity;
        this.isReserved = false;
    }

    public void reserveTable() {
        isReserved = true;
    }

    public void releaseTable() {
        isReserved = false;
    }

    // Getters and setters...
}
```
### Order Class
Manages a food order.
```java
import java.util.HashMap;
import java.util.Map;

public class Order {
    private int orderId;
    private Map<String, Integer> items; // Item name and quantity

    public Order(int orderId) {
        this.orderId = orderId;
        this.items = new HashMap<>();
    }

    public void addItem(String itemName, int quantity) {
        items.put(itemName, items.getOrDefault(itemName, 0) + quantity);
    }

    // Getters and setters...
}
```
### Inventory Class
Tracks kitchen inventory and supplies.
```java
import java.util.HashMap;
import java.util.Map;

public class Inventory {
    private Map<String, Integer> stock;

    public Inventory() {
        this.stock = new HashMap<>();
    }

    public void updateStock(String itemName, int quantity) {
        stock.put(itemName, quantity);
    }

    public boolean isItemAvailable(String itemName, int quantityNeeded) {
        return stock.getOrDefault(itemName, 0) >= quantityNeeded;
    }

    public int getStock(String itemName) {
        return stock.getOrDefault(itemName, 0);
    }

    // Getters and setters...
}
```
### Bill Class
Represents a customer's bill.
```java
public class Bill {
    private int billId;
    private Order order;
    private double totalAmount;

    public Bill(int billId, Order order) {
        this.billId = billId;
        this.order = order;
        this.totalAmount = calculateTotal(order);
    }

    private double calculateTotal(Order order) {
        // Calculate the total bill amount based on the order
        // This could involve fetching prices for each item in the order
        return 0.0; // Placeholder for total calculation
    }

    // Getters and setters...
}
```
### RestaurantManagementSystem Class
Main class that manages the restaurant operations.
```java
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class RestaurantManagementSystem {
    private List<Table> tables;
    private Inventory inventory;

    public RestaurantManagementSystem() {
        this.tables = new ArrayList<>();
        this.inventory = new Inventory();
        // Initialize tables and inventory
        initializeTables();
    }

    private void initializeTables() {
        // Assuming the restaurant has 10 tables with varying seating capacities
        for (int i = 1; i <= 10; i++) {
            tables.add(new Table(i, i + 2)); // Example: Table ID 1 with 3 seats, etc.
        }
    }

    public Table reserveTable(int tableId) {
        // Find and reserve a table based on tableId
        for (Table table : tables) {
            if (table.getTableId() == tableId && !table.isReserved()) {
                table.reserveTable();
                return table;
            }
        }
        return null; // No table available or invalid tableId
    }

    public Order placeOrder(int orderId, Map<String, Integer> items) {
        // Place a new food order
        Order newOrder = new Order(orderId);
        for (Map.Entry<String, Integer> item : items.entrySet()) {
            String itemName = item.getKey();
            int quantity = item.getValue();

            if (inventory.isItemAvailable(itemName, quantity)) {
                newOrder.addItem(itemName, quantity);
                inventory.updateStock(itemName, inventory.getStock(itemName) - quantity);
            } else {
                // Handle case where item is not available
                System.out.println("Item not available: " + itemName);
            }
        }
        return newOrder;
    }

    // Other necessary methods...
}
```