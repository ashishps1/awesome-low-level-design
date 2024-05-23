package onlineshopping;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ShoppingCart {
    private final Map<String, OrderItem> items;

    public ShoppingCart() {
        this.items = new HashMap<>();
    }

    public void addItem(Product product, int quantity) {
        String productId = product.getId();
        if (items.containsKey(productId)) {
            OrderItem item = items.get(productId);
            quantity += item.getQuantity();
        }
        items.put(productId, new OrderItem(product, quantity));
    }

    public void removeItem(String productId) {
        items.remove(productId);
    }

    public void updateItemQuantity(String productId, int quantity) {
        OrderItem item = items.get(productId);
        if (item != null) {
            items.put(productId, new OrderItem(item.getProduct(), quantity));
        }
    }

    public List<OrderItem> getItems() {
        return new ArrayList<>(items.values());
    }

    public void clear() {
        items.clear();
    }
}
