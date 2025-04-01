package onlinestockbrokeragesystem;

import java.util.Map;
import java.util.Queue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class StockBroker {
    private static StockBroker instance;
    private final Map<String, Account> accounts;
    private final Map<String, Stock> stocks;
    private final Queue<Order> orderQueue;
    private final AtomicInteger accountIdCounter;

    private StockBroker() {
        accounts = new ConcurrentHashMap<>();
        stocks = new ConcurrentHashMap<>();
        orderQueue = new ConcurrentLinkedQueue<>();
        accountIdCounter = new AtomicInteger(1);
    }

    public static synchronized StockBroker getInstance() {
        if (instance == null) {
            instance = new StockBroker();
        }
        return instance;
    }

    public void createAccount(User user, double initialBalance) {
        String accountId = generateAccountId();
        Account account = new Account(accountId, user, initialBalance);
        accounts.put(accountId, account);
    }

    public Account getAccount(String accountId) {
        return accounts.get(accountId);
    }

    public void addStock(Stock stock) {
        stocks.put(stock.getSymbol(), stock);
    }

    public Stock getStock(String symbol) {
        return stocks.get(symbol);
    }

    public void placeOrder(Order order) {
        orderQueue.offer(order);
        processOrders();
    }

    private void processOrders() {
        while (!orderQueue.isEmpty()) {
            Order order = orderQueue.poll();
            try {
                order.execute();
            } catch (InsufficientFundsException | InsufficientStockException e) {
                // Handle exception and notify user
                System.out.println("Order failed: " + e.getMessage());
            }
        }
    }

    private String generateAccountId() {
        int accountId = accountIdCounter.getAndIncrement();
        return "A" + String.format("%03d", accountId);
    }
}
