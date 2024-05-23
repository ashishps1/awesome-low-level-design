package onlineshopping;

import java.util.List;

public class Order {
    private final String id;
    private final User user;
    private final List<OrderItem> items;
    private final double totalAmount;
    private OrderStatus status;

    public Order(String id, User user, List<OrderItem> items) {
        this.id = id;
        this.user = user;
        this.items = items;
        this.totalAmount = calculateTotalAmount();
        this.status = OrderStatus.PENDING;
    }

    private double calculateTotalAmount() {
        return items.stream().mapToDouble(item -> item.getProduct().getPrice() * item.getQuantity()).sum();
    }

    public void setStatus(OrderStatus status) {
        this.status = status;
    }

    public String getId() {
        return id;
    }

    public User getUser() {
        return user;
    }

    public List<OrderItem> getItems() {
        return items;
    }

    public double getTotalAmount() {
        return totalAmount;
    }

    public OrderStatus getStatus() {
        return status;
    }
}
