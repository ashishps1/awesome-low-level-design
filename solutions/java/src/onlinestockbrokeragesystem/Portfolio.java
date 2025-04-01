package onlinestockbrokeragesystem;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class Portfolio {
    private final Account account;
    private final Map<String, Integer> holdings;

    public Portfolio(Account account) {
        this.account = account;
        this.holdings = new ConcurrentHashMap<>();
    }

    public synchronized void addStock(Stock stock, int quantity) {
        holdings.put(stock.getSymbol(), holdings.getOrDefault(stock.getSymbol(), 0) + quantity);
    }

    public synchronized void removeStock(Stock stock, int quantity) {
        String symbol = stock.getSymbol();
        if (holdings.containsKey(symbol)) {
            int currentQuantity = holdings.get(symbol);
            if (currentQuantity > quantity) {
                holdings.put(symbol, currentQuantity - quantity);
            } else if (currentQuantity == quantity) {
                holdings.remove(symbol);
            } else {
                throw new InsufficientStockException("Insufficient stock quantity in the portfolio.");
            }
        } else {
            throw new InsufficientStockException("Stock not found in the portfolio.");
        }
    }

    public Map<String, Integer> getHoldings() {
        return holdings;
    }
}
