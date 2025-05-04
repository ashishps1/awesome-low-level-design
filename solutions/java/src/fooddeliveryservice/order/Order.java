package fooddeliveryservice.order;

import fooddeliveryservice.*;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class Order {
    private final String id;
    private final Customer customer;
    private final Restaurant restaurant;
    private final List<MenuItem> orderItems;
    private OrderStatus status;
    private DeliveryAgent deliveryAgent;

    public Order(String id, Customer customer, Restaurant restaurant) {
        this.id = id;
        this.customer = customer;
        this.restaurant = restaurant;
        this.orderItems = new ArrayList<>();
        this.status = OrderStatus.PENDING;
    }

    public Order(Customer customer, Restaurant restaurant, List<MenuItem> items) {
        this.id = "ORD" + UUID.randomUUID().toString().toUpperCase();
        this.customer = customer;
        this.restaurant = restaurant;
        this.orderItems = items;
        this.status = OrderStatus.PENDING;
    }

    public void addItem(MenuItem item) {
        orderItems.add(item);
    }

    public void removeItem(MenuItem item) {
        orderItems.remove(item);
    }

    public void updateStatus(OrderStatus status) {
        this.status = status;
    }

    public void assignDeliveryAgent(DeliveryAgent agent) {
        deliveryAgent = agent;
    }

    public String getId() {
        return id;
    }

    public OrderStatus getStatus() {
        return status;
    }

    public DeliveryAgent getDeliveryAgent() {
        return deliveryAgent;
    }
}
