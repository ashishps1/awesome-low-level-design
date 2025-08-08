package onlineshoppingservice.state;

import onlineshoppingservice.models.Order;

public interface OrderState {
    void ship(Order order);
    void deliver(Order order);
    void cancel(Order order);
}
