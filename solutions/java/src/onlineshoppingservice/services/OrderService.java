package onlineshoppingservice.services;

import onlineshoppingservice.models.Customer;
import onlineshoppingservice.models.Order;
import onlineshoppingservice.models.OrderLineItem;
import onlineshoppingservice.models.ShoppingCart;

import java.util.ArrayList;
import java.util.List;

public class OrderService {
    private final InventoryService inventoryService;

    public OrderService(InventoryService inventoryService) {
        this.inventoryService = inventoryService;
    }

    public Order createOrder(Customer customer, ShoppingCart cart) {
        List<OrderLineItem> result = new ArrayList<>();
        cart.getItems().values().stream()
            .map(cartItem -> new OrderLineItem(
                    cartItem.getProduct().getId(),
                    cartItem.getProduct().getName(),
                    cartItem.getQuantity(),
                    cartItem.getProduct().getPrice()))
            .forEach(result::add);

        inventoryService.updateStockForOrder(result);

        return new Order(customer, result, customer.getShippingAddress(), cart.calculateTotal());
    }
}
