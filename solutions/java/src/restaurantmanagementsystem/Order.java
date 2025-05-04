package restaurantmanagementsystem;

import java.util.List;
import java.util.UUID;

public class Order {
    private final String id;
    private final List<OrderItem> items;
    private OrderStatus status;
    private final Table table;

    public Order(Table table, List<OrderItem> items) {
        this.id = UUID.randomUUID().toString();
        this.table = table;
        this.items = items;
        this.status = OrderStatus.PENDING;
    }

    public void markPreparing() {
        this.status = OrderStatus.PREPARING;
    }

    public void markReady() {
        this.status = OrderStatus.READY;
    }

    public void markServed() {
        this.status = OrderStatus.SERVED;
    }

    public void markPaid() {
        this.status = OrderStatus.PAID;
    }

    public double calculateTotal() {
        return items.stream().mapToDouble(OrderItem::getSubtotal).sum();
    }

    public void setStatus(OrderStatus status) {
        this.status = status;
    }

    public String getId() {
        return id;
    }

    public List<OrderItem> getItems() {
        return items;
    }

    public OrderStatus getStatus() {
        return status;
    }
}
