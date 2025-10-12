package restaurantmanagementsystem.command;

import restaurantmanagementsystem.model.Chef;
import restaurantmanagementsystem.model.Order;

public class PrepareOrderCommand implements Command {
    private final Order order;
    private final Chef chef;

    public PrepareOrderCommand(Order order, Chef chef) {
        this.order = order;
        this.chef = chef;
    }

    @Override
    public void execute() {
        chef.prepareOrder(order);
    }
}
