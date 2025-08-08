package onlinestockbrokeragesystem;

import onlinestockbrokeragesystem.entities.Order;
import onlinestockbrokeragesystem.entities.OrderBuilder;
import onlinestockbrokeragesystem.entities.Stock;
import onlinestockbrokeragesystem.entities.User;

public class StockBrokerageSystemDemo {
    public static void main(String[] args) throws InterruptedException {
        // --- System Setup ---
        StockBrokerageSystem system = StockBrokerageSystem.getInstance();

        // --- Create Stocks ---
        Stock apple = system.addStock("AAPL", 150.00);
        Stock google = system.addStock("GOOG", 2800.00);

        // --- Create Members (Users) ---
        User alice = system.registerUser("Alice", 20000.00);
        User bob = system.registerUser("Bob", 25000.00);

        // Bob already owns some Apple stock
        bob.getAccount().addStock("AAPL", 50);

        // --- Members subscribe to stock notifications (Observer Pattern) ---
        apple.addObserver(alice);
        google.addObserver(alice);
        apple.addObserver(bob);

        System.out.println("--- Initial State ---");
        printAccountStatus(alice);
        printAccountStatus(bob);

        System.out.println("\n--- Trading Simulation Starts ---\n");

        // --- SCENARIO 1: Limit Order Match ---
        System.out.println("--- SCENARIO 1: Alice places a limit buy, Bob places a limit sell that matches ---");

        // Alice wants to buy 10 shares of AAPL if the price is $150.50 or less
        Order aliceBuyOrder = new OrderBuilder()
                .forUser(alice)
                .buy(10)
                .withStock(apple)
                .withLimit(150.50)
                .build();
        system.placeBuyOrder(aliceBuyOrder);

        // Bob wants to sell 20 of his shares if the price is $150.50 or more
        Order bobSellOrder = new OrderBuilder()
                .forUser(bob)
                .sell(20)
                .withStock(apple)
                .withLimit(150.50)
                .build();
        system.placeSellOrder(bobSellOrder);

        // The exchange will automatically match and execute this trade.
        // Let's check the status after the trade.
        Thread.sleep(100); // Give time for notifications to print
        System.out.println("\n--- Account Status After Trade 1 ---");
        printAccountStatus(alice);
        printAccountStatus(bob);

        // --- SCENARIO 2: Price Update triggers notifications ---
        System.out.println("\n--- SCENARIO 2: Market price of GOOG changes ---");
        google.setPrice(2850.00); // Alice will get a notification

        // --- SCENARIO 3: Order Cancellation (State Pattern) ---
        System.out.println("\n--- SCENARIO 3: Alice places an order and then cancels it ---");
        Order aliceCancelOrder = new OrderBuilder()
                .forUser(alice)
                .buy(5)
                .withStock(google)
                .withLimit(2700.00) // Price is too low, so it won't execute immediately
                .build();
        system.placeBuyOrder(aliceCancelOrder);

        System.out.println("Order status before cancellation: " + aliceCancelOrder.getStatus());
        system.cancelOrder(aliceCancelOrder);
        System.out.println("Order status after cancellation attempt: " + aliceCancelOrder.getStatus());

        // Now try to cancel an already filled order
        System.out.println("\n--- Trying to cancel an already FILLED order (State Pattern) ---");
        System.out.println("Bob's sell order status: " + bobSellOrder.getStatus());
        system.cancelOrder(bobSellOrder); // This should fail
        System.out.println("Bob's sell order status after cancel attempt: " + bobSellOrder.getStatus());
    }

    private static void printAccountStatus(User user) {
        System.out.printf("Member: %s, Cash: $%.2f, Portfolio: %s%n",
                user.getName(),
                user.getAccount().getBalance(),
                user.getAccount().getPortfolio());
    }
}
