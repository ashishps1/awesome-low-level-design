package restaurantmanagementsystem.decorator;

import restaurantmanagementsystem.model.Order;

public class BaseBill implements BillComponent {
    private final Order order;
    public BaseBill(Order order) { this.order = order; }

    @Override
    public double calculateTotal() { return order.getTotalPrice(); }

    @Override
    public String getDescription() { return "Order Items"; }
}
