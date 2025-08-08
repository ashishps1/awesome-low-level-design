package fooddeliveryservice.observer;

import fooddeliveryservice.order.Order;

public interface OrderObserver {
    void onUpdate(Order order);
}
