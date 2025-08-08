package onlineshoppingservice.state;

import onlineshoppingservice.enums.OrderStatus;
import onlineshoppingservice.models.Order;

public class ShippedState implements OrderState {
    @Override
    public void ship(Order order) { System.out.println("Order is already shipped."); }

    @Override
    public void deliver(Order order) {
        System.out.println("Delivering order " + order.getId());
        order.setStatus(OrderStatus.DELIVERED);
        order.setState(new DeliveredState());
    }

    @Override
    public void cancel(Order order) { System.out.println("Cannot cancel a shipped order."); }
}
