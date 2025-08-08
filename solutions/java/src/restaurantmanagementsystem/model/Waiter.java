package restaurantmanagementsystem.model;

import restaurantmanagementsystem.observer.OrderObserver;
import restaurantmanagementsystem.state.ServedState;

public class Waiter extends Staff implements OrderObserver {
    public Waiter(String id, String name) {
        super(id, name);
    }

    public void serveOrder(Order order) {
        System.out.println("Waiter " + name + " is serving order " + order.getOrderId());
        order.getOrderItems().forEach(item -> {
            item.changeState(new ServedState());
        });
    }

    @Override
    public void update(OrderItem item) {
        System.out.println(">>> WAITER " + name + " NOTIFIED: Item '" +
                item.getMenuItem().getName() + "' for table " +
                item.getOrder().getTableId() + " is READY FOR PICKUP.");
    }
}