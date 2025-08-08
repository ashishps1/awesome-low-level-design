package restaurantmanagementsystem.state;

import restaurantmanagementsystem.model.OrderItem;

public class ServedState implements OrderItemState {
    @Override
    public void next(OrderItem item) {
        System.out.println("This is the final state.");
    }

    @Override
    public void prev(OrderItem item) {
        System.out.println("Cannot revert a served item.");
    }

    @Override
    public String getStatus() { return "SERVED"; }
}
