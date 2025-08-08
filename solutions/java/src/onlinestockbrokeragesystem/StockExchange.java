package onlinestockbrokeragesystem;

import onlinestockbrokeragesystem.enums.OrderStatus;
import onlinestockbrokeragesystem.enums.OrderType;
import onlinestockbrokeragesystem.entities.Order;
import onlinestockbrokeragesystem.entities.Stock;
import onlinestockbrokeragesystem.entities.User;
import onlinestockbrokeragesystem.state.FilledState;

import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;

public class StockExchange {
    private static volatile StockExchange instance;
    private final Map<String, List<Order>> buyOrders;
    private final Map<String, List<Order>> sellOrders;

    private StockExchange() {
        this.buyOrders = new ConcurrentHashMap<>();
        this.sellOrders = new ConcurrentHashMap<>();
    }

    public static StockExchange getInstance() {
        if (instance == null) {
            synchronized (StockExchange.class) {
                if (instance == null) {
                    instance = new StockExchange();
                }
            }
        }
        return instance;
    }

    public void placeBuyOrder(Order order) {
        buyOrders.computeIfAbsent(order.getStock().getSymbol(), k -> new CopyOnWriteArrayList<>()).add(order);
        matchOrders(order.getStock());
    }

    public void placeSellOrder(Order order) {
        sellOrders.computeIfAbsent(order.getStock().getSymbol(), k -> new CopyOnWriteArrayList<>()).add(order);
        matchOrders(order.getStock());
    }

    private void matchOrders(Stock stock) {
        synchronized (this) { // Critical section to prevent race conditions during matching
            List<Order> buys = buyOrders.get(stock.getSymbol());
            List<Order> sells = sellOrders.get(stock.getSymbol());

            if (buys == null || sells == null) return;

            boolean matchFound;
            do {
                matchFound = false;
                Order bestBuy = findBestBuy(buys);
                Order bestSell = findBestSell(sells);

                if (bestBuy != null && bestSell != null) {
                    double buyPrice = bestBuy.getType() == OrderType.MARKET ? stock.getPrice() : bestBuy.getPrice();
                    double sellPrice = bestSell.getType() == OrderType.MARKET ? stock.getPrice() : bestSell.getPrice();

                    if (buyPrice >= sellPrice) {
                        executeTrade(bestBuy, bestSell, sellPrice); // Trade at the seller's asking price
                        matchFound = true;
                    }
                }
            } while (matchFound);
        }
    }

    private void executeTrade(Order buyOrder, Order sellOrder, double tradePrice) {
        System.out.printf("--- Executing Trade for %s at $%.2f ---%n", buyOrder.getStock(), tradePrice);

        User buyer = buyOrder.getUser();
        User seller = sellOrder.getUser();

        int tradeQuantity = Math.min(buyOrder.getQuantity(), sellOrder.getQuantity());
        double totalCost = tradeQuantity * tradePrice;

        // Perform transaction
        buyer.getAccount().debit(totalCost);
        buyer.getAccount().addStock(buyOrder.getStock().getSymbol(), tradeQuantity);

        seller.getAccount().credit(totalCost);
        seller.getAccount().removeStock(sellOrder.getStock().getSymbol(), tradeQuantity);

        // Update orders
        updateOrderStatus(buyOrder, tradeQuantity);
        updateOrderStatus(sellOrder, tradeQuantity);

        // Update stock's market price to last traded price
        buyOrder.getStock().setPrice(tradePrice);

        System.out.println("--- Trade Complete ---");
    }

    private void updateOrderStatus(Order order, int quantityTraded) {
        // This is a simplified update logic. A real system would handle partial fills.
        order.setStatus(OrderStatus.FILLED);
        order.setState(new FilledState());
        String stockSymbol = order.getStock().getSymbol();
        // Remove from books
        if (buyOrders.get(stockSymbol) != null)
            buyOrders.get(stockSymbol).remove(order);
        if (sellOrders.get(stockSymbol) != null)
            sellOrders.get(stockSymbol).remove(order);
    }

    private Order findBestBuy(List<Order> buys) {
        return buys.stream()
                .filter(o -> o.getStatus() == OrderStatus.OPEN)
                .max(Comparator.comparingDouble(Order::getPrice)) // Highest limit price is best
                .orElse(null);
    }

    private Order findBestSell(List<Order> sells) {
        return sells.stream()
                .filter(o -> o.getStatus() == OrderStatus.OPEN)
                .min(Comparator.comparingDouble(Order::getPrice)) // Lowest limit price is best
                .orElse(null);
    }
}
