package restaurantmanagementsystem.state;

import restaurantmanagementsystem.model.OrderItem;

public interface OrderItemState {
    void next(OrderItem item);
    void prev(OrderItem item);
    String getStatus();
}
