package restaurantmanagementsystem.model;

import restaurantmanagementsystem.state.PreparingState;

public class Chef extends Staff {
    public Chef(String id, String name) {
        super(id, name);
    }

    public void prepareOrder(Order order) {
        System.out.println("Chef " + name + " received order " + order.getOrderId() + " and is starting preparation.");
        order.getOrderItems().forEach(item -> {
            // Chef's action triggers the first state change for each item.
            item.changeState(new PreparingState());
        });
    }
}