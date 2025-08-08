package onlineshoppingservice.observer;

import onlineshoppingservice.models.Order;

public interface OrderObserver {
    void update(Order order);
}
