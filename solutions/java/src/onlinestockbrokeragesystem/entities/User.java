package onlinestockbrokeragesystem.entities;

import onlinestockbrokeragesystem.observer.StockObserver;

import java.util.UUID;

public class User implements StockObserver {
    private final String userId;
    private final String name;
    private final Account account;

    public User(String name, double initialCash) {
        this.userId = UUID.randomUUID().toString();
        this.name = name;
        this.account = new Account(initialCash);
    }

    public String getUserId() { return userId; }
    public String getName() { return name; }
    public Account getAccount() { return account; }

    @Override
    public void update(Stock stock) {
        System.out.printf("[Notification for %s] Stock %s price updated to: $%.2f%n",
                name, stock.getSymbol(), stock.getPrice());
    }

    public void orderStatusUpdate(Order order) {
        System.out.printf("[Order Notification for %s] Order %s for %s is now %s.%n",
                name, order.getOrderId(), order.getStock(), order.getStatus());
    }
}
