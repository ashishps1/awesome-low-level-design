package onlineshoppingservice.state;

import onlineshoppingservice.models.Order;

public class CancelledState implements OrderState {
    @Override
    public void ship(Order order) { System.out.println("Cannot ship a cancelled order."); }

    @Override
    public void deliver(Order order) { System.out.println("Cannot deliver a cancelled order."); }

    @Override
    public void cancel(Order order) { System.out.println("Order is already cancelled."); }
}
