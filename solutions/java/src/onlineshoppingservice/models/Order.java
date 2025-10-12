package onlineshoppingservice.models;

import onlineshoppingservice.enums.OrderStatus;
import onlineshoppingservice.observer.Subject;
import onlineshoppingservice.state.OrderState;
import onlineshoppingservice.state.PlacedState;

import java.time.LocalDateTime;
import java.util.List;
import java.util.UUID;

public class Order extends Subject {
    private final String id;
    private final Customer customer;
    private final List<OrderLineItem> items;
    private final Address shippingAddress;
    private final double totalAmount;
    private final LocalDateTime orderDate;
    private OrderStatus status;
    private OrderState currentState;

    public Order(Customer customer, List<OrderLineItem> items, Address shippingAddress, double totalAmount) {
        this.id = UUID.randomUUID().toString().substring(0, 8);
        this.customer = customer;
        this.items = items;
        this.shippingAddress = shippingAddress;
        this.totalAmount = totalAmount;
        this.orderDate = LocalDateTime.now();
        this.status = OrderStatus.PLACED;
        this.currentState = new PlacedState();
        addObserver(customer);
    }

    // State Pattern methods
    public void shipOrder() { currentState.ship(this); }
    public void deliverOrder() { currentState.deliver(this); }
    public void cancelOrder() { currentState.cancel(this); }

    // Getters and Setters
    public String getId() { return id; }
    public OrderStatus getStatus() { return status; }
    public void setState(OrderState state) { this.currentState = state; }
    public void setStatus(OrderStatus status) {
        this.status = status;
        notifyObservers(this);
    }
    public List<OrderLineItem> getItems() { return items; }
}
