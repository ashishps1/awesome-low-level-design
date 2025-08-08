package onlinestockbrokeragesystem.entities;

import onlinestockbrokeragesystem.enums.OrderStatus;
import onlinestockbrokeragesystem.enums.OrderType;
import onlinestockbrokeragesystem.state.OpenState;
import onlinestockbrokeragesystem.state.OrderState;
import onlinestockbrokeragesystem.strategy.ExecutionStrategy;

public class Order {
    private final String orderId;
    private final User user;
    private final Stock stock;
    private final OrderType type;
    private final int quantity;
    private final double price; // Limit price for Limit orders
    private OrderStatus status;
    private User owner;
    private OrderState currentState;
    private final ExecutionStrategy executionStrategy;

    public Order(String orderId, User user, Stock stock, OrderType type, int quantity, double price, ExecutionStrategy strategy, User owner) {
        this.orderId = orderId;
        this.user = user;
        this.stock = stock;
        this.type = type;
        this.quantity = quantity;
        this.price = price;
        this.executionStrategy = strategy;
        this.owner = owner;
        this.currentState = new OpenState(); // Initial state
        this.status = OrderStatus.OPEN;
    }

    // State pattern methods
    public void cancel() {
        currentState.cancel(this);
    }

    // Getters
    public String getOrderId() { return orderId; }
    public User getUser() { return user; }
    public Stock getStock() { return stock; }
    public OrderType getType() { return type; }
    public int getQuantity() { return quantity; }
    public double getPrice() { return price; }
    public OrderStatus getStatus() { return status; }
    public ExecutionStrategy getExecutionStrategy() { return executionStrategy; }

    // Setters for state transitions
    public void setState(OrderState state) {
        this.currentState = state;
    }

    public void setStatus(OrderStatus status) {
        this.status = status;
        notifyOwner();
    }

    private void notifyOwner() {
        if (owner != null) {
            owner.orderStatusUpdate(this);
        }
    }
}