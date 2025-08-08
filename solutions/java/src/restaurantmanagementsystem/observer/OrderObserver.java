package restaurantmanagementsystem.observer;

import restaurantmanagementsystem.model.OrderItem;

public interface OrderObserver {
    void update(OrderItem item);
}
