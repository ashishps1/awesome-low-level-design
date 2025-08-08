package onlineshoppingservice.state;

import onlineshoppingservice.enums.OrderStatus;
import onlineshoppingservice.models.Order;

public class PlacedState implements OrderState {
    @Override
    public void ship(Order order) {
        System.out.println("Shipping order " + order.getId());
        order.setStatus(OrderStatus.SHIPPED);
        order.setState(new ShippedState());
    }

    @Override
    public void deliver(Order order) { System.out.println("Cannot deliver an order that has not been shipped."); }

    @Override
    public void cancel(Order order) {
        System.out.println("Cancelling order " + order.getId());
        order.setStatus(OrderStatus.CANCELLED);
        order.setState(new CancelledState());
    }
}
