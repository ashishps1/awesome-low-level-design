package restaurantmanagementsystem.model;

import java.util.ArrayList;
import java.util.List;

public class Order {
    private final int orderId;
    private final int tableId;
    private final List<OrderItem> items = new ArrayList<>();

    public Order(int orderId, int tableId) {
        this.orderId = orderId;
        this.tableId = tableId;
    }

    public void addItem(OrderItem item) {
        items.add(item);
    }

    public double getTotalPrice() {
        return items.stream()
                .mapToDouble(item -> item.getMenuItem().getPrice())
                .sum();
    }

    public int getOrderId() { return orderId; }
    public int getTableId() { return tableId; }
    public List<OrderItem> getOrderItems() { return items; }
}