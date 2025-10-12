package fooddeliveryservice.order;

import fooddeliveryservice.entity.Customer;
import fooddeliveryservice.entity.DeliveryAgent;
import fooddeliveryservice.entity.Restaurant;
import fooddeliveryservice.observer.OrderObserver;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class Order {
    private final String id;
    private final Customer customer;
    private final Restaurant restaurant;
    private final List<OrderItem> items;
    private OrderStatus status;
    private DeliveryAgent deliveryAgent;
    private final List<OrderObserver> observers = new ArrayList<>();

    public Order(Customer customer, Restaurant restaurant, List<OrderItem> items) {
        this.id = UUID.randomUUID().toString();
        this.customer = customer;
        this.restaurant = restaurant;
        this.items = items;
        this.status = OrderStatus.PENDING;
        addObserver(customer);
        addObserver(restaurant);
    }

    public void addObserver(OrderObserver observer) { observers.add(observer); }
    private void notifyObservers() { observers.forEach(o -> o.onUpdate(this)); }

    public void setStatus(OrderStatus newStatus) {
        if (this.status != newStatus) {
            this.status = newStatus;
            notifyObservers();
        }
    }

    public boolean cancel() {
        // Only allow cancellation if the order is still in the PENDING state.
        if (this.status == OrderStatus.PENDING) {
            setStatus(OrderStatus.CANCELLED);
            return true;
        }
        return false;
    }

    public void assignDeliveryAgent(DeliveryAgent agent) {
        this.deliveryAgent = agent;
        addObserver(agent);
        agent.setAvailable(false); // Mark agent as busy
    }

    // Getters
    public String getId() { return id; }
    public OrderStatus getStatus() { return status; }
    public Customer getCustomer() { return customer; }
    public Restaurant getRestaurant() { return restaurant; }
    public DeliveryAgent getDeliveryAgent() { return deliveryAgent; }
}
