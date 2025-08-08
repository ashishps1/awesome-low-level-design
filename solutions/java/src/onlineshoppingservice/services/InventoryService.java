package onlineshoppingservice.services;

import onlineshoppingservice.exceptions.OutOfStockException;
import onlineshoppingservice.models.OrderLineItem;
import onlineshoppingservice.models.Product;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class InventoryService {
    private final Map<String, Integer> stock; // productId -> quantity

    public InventoryService() {
        this.stock = new ConcurrentHashMap<>();
    }

    public void addStock(Product product, int quantity) {
        stock.put(product.getId(), stock.getOrDefault(product.getId(), 0) + quantity);
    }

    public synchronized void updateStockForOrder(List<OrderLineItem> items) {
        // First, check if all items are in stock
        for (OrderLineItem item : items) {
            if (stock.getOrDefault(item.getProductId(), 0) < item.getQuantity()) {
                throw new OutOfStockException("Not enough stock for product ID: " + item.getProductId());
            }
        }
        // If all checks pass, deduct the stock
        for (OrderLineItem item : items) {
            stock.compute(item.getProductId(), (id, currentStock) -> currentStock - item.getQuantity());
        }
    }
}
