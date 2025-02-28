using System;

namespace OnlineStockBrokerageSystem
{
    public class StockBrokerageSystemDemo
    {
        public static void Run()
        {
            var stockBroker = StockBroker.GetInstance();

            // Create user and account
            var user = new User("U001", "John Doe", "john@example.com");
            stockBroker.CreateAccount(user, 10000.0);
            var account = stockBroker.GetAccount("A001");

            // Add stocks to the stock broker
            var stock1 = new Stock("AAPL", "Apple Inc.", 150.0);
            var stock2 = new Stock("GOOGL", "Alphabet Inc.", 2000.0);
            stockBroker.AddStock(stock1);
            stockBroker.AddStock(stock2);

            // Place buy orders
            var buyOrder1 = new BuyOrder("O001", account, stock1, 10, 150.0);
            var buyOrder2 = new BuyOrder("O002", account, stock2, 5, 2000.0);
            stockBroker.PlaceOrder(buyOrder1);
            stockBroker.PlaceOrder(buyOrder2);

            // Place sell orders
            var sellOrder1 = new SellOrder("O003", account, stock1, 5, 160.0);
            stockBroker.PlaceOrder(sellOrder1);

            // Print account balance and portfolio
            Console.WriteLine($"Account Balance: ${account.GetBalance()}");
            Console.WriteLine($"Portfolio: {string.Join(", ", account.Portfolio.GetHoldings())}");
        }
    }
}