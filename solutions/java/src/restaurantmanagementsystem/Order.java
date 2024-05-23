package restaurantmanagementsystem;

import java.sql.Timestamp;
import java.util.List;

public class Order {
    private int id;
    private List<MenuItem> items;
    private double totalAmount;
    private OrderStatus status;
    private Timestamp timestamp;

    public Order(int id, List<MenuItem> items, double totalAmount, OrderStatus status, Timestamp timestamp) {
        this.id = id;
        this.items = items;
        this.totalAmount = totalAmount;
        this.status = status;
        this.timestamp = timestamp;
    }

    public void setStatus(OrderStatus status) {
        this.status = status;
    }

    public int getId() {
        return id;
    }

    public List<MenuItem> getItems() {
        return items;
    }

    public double getTotalAmount() {
        return totalAmount;
    }

    public OrderStatus getStatus() {
        return status;
    }

    public Timestamp getTimestamp() {
        return timestamp;
    }
}
