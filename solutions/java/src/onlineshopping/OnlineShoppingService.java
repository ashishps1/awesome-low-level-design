package onlineshopping;

import onlineshopping.payment.Payment;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

public class OnlineShoppingService {
    private static OnlineShoppingService instance;
    private final Map<String, User> users;
    private final Map<String, Product> products;
    private final Map<String, Order> orders;

    private OnlineShoppingService() {
        users = new ConcurrentHashMap<>();
        products = new ConcurrentHashMap<>();
        orders = new ConcurrentHashMap<>();
    }

    public static synchronized OnlineShoppingService getInstance() {
        if (instance == null) {
            instance = new OnlineShoppingService();
        }
        return instance;
    }

    public void registerUser(User user) {
        users.put(user.getId(), user);
    }

    public User getUser(String userId) {
        return users.get(userId);
    }

    public void addProduct(Product product) {
        products.put(product.getId(), product);
    }

    public Product getProduct(String productId) {
        return products.get(productId);
    }

    public List<Product> searchProducts(String keyword) {
        return products.values().stream()
                .filter(product -> product.getName().toLowerCase().contains(keyword.toLowerCase()))
                .collect(Collectors.toList());
    }

    public synchronized Order placeOrder(User user, ShoppingCart cart, Payment payment) {
        List<OrderItem> orderItems = new ArrayList<>();
        for (OrderItem item : cart.getItems()) {
            Product product = item.getProduct();
            int quantity = item.getQuantity();
            if (product.isAvailable(quantity)) {
                product.updateQuantity(-quantity);
                orderItems.add(item);
            }
        }

        if (orderItems.isEmpty()) {
            throw new IllegalStateException("No available products in the cart.");
        }

        String orderId = generateOrderId();
        Order order = new Order(orderId, user, orderItems);
        orders.put(orderId, order);
        user.addOrder(order);
        cart.clear();

        if (payment.processPayment(order.getTotalAmount())) {
            order.setStatus(OrderStatus.PROCESSING);
        } else {
            order.setStatus(OrderStatus.CANCELLED);
            // Revert the product quantities
            for (OrderItem item : orderItems) {
                Product product = item.getProduct();
                int quantity = item.getQuantity();
                product.updateQuantity(quantity);
            }
        }

        return order;
    }

    public Order getOrder(String orderId) {
        return orders.get(orderId);
    }

    private String generateOrderId() {
        return "ORDER" + UUID.randomUUID().toString().substring(0, 8).toUpperCase();
    }
}
