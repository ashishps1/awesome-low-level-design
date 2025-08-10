using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

public class StockBrokerageSystemDemo
{
    public static void Main(string[] args)
    {
        // System Setup
        var system = StockBrokerageSystem.GetInstance();

        // Create Stocks
        var apple = system.AddStock("AAPL", 150.00);
        var google = system.AddStock("GOOG", 2800.00);

        // Create Members (Users)
        var alice = system.RegisterUser("Alice", 20000.00);
        var bob = system.RegisterUser("Bob", 25000.00);

        // Bob already owns some Apple stock
        bob.GetAccount().AddStock("AAPL", 50);

        // Members subscribe to stock notifications (Observer Pattern)
        apple.AddObserver(alice);
        google.AddObserver(alice);
        apple.AddObserver(bob);

        Console.WriteLine("--- Initial State ---");
        PrintAccountStatus(alice);
        PrintAccountStatus(bob);

        Console.WriteLine("\n--- Trading Simulation Starts ---\n");

        // SCENARIO 1: Limit Order Match
        Console.WriteLine("--- SCENARIO 1: Alice places a limit buy, Bob places a limit sell that matches ---");

        // Alice wants to buy 10 shares of AAPL if the price is $150.50 or less
        var aliceBuyOrder = new OrderBuilder()
            .ForUser(alice)
            .Buy(10)
            .WithStock(apple)
            .WithLimit(150.50)
            .Build();
        system.PlaceBuyOrder(aliceBuyOrder);

        // Bob wants to sell 20 of his shares if the price is $150.50 or more
        var bobSellOrder = new OrderBuilder()
            .ForUser(bob)
            .Sell(20)
            .WithStock(apple)
            .WithLimit(150.50)
            .Build();
        system.PlaceSellOrder(bobSellOrder);

        // The exchange will automatically match and execute this trade.
        Thread.Sleep(100); // Give time for notifications to print
        Console.WriteLine("\n--- Account Status After Trade 1 ---");
        PrintAccountStatus(alice);
        PrintAccountStatus(bob);

        // SCENARIO 2: Price Update triggers notifications
        Console.WriteLine("\n--- SCENARIO 2: Market price of GOOG changes ---");
        google.SetPrice(2850.00); // Alice will get a notification

        // SCENARIO 3: Order Cancellation (State Pattern)
        Console.WriteLine("\n--- SCENARIO 3: Alice places an order and then cancels it ---");
        var aliceCancelOrder = new OrderBuilder()
            .ForUser(alice)
            .Buy(5)
            .WithStock(google)
            .WithLimit(2700.00) // Price is too low, so it won't execute immediately
            .Build();
        system.PlaceBuyOrder(aliceCancelOrder);

        Console.WriteLine($"Order status before cancellation: {aliceCancelOrder.GetStatus()}");
        system.CancelOrder(aliceCancelOrder);
        Console.WriteLine($"Order status after cancellation attempt: {aliceCancelOrder.GetStatus()}");

        // Now try to cancel an already filled order
        Console.WriteLine("\n--- Trying to cancel an already FILLED order (State Pattern) ---");
        Console.WriteLine($"Bob's sell order status: {bobSellOrder.GetStatus()}");
        system.CancelOrder(bobSellOrder); // This should fail
        Console.WriteLine($"Bob's sell order status after cancel attempt: {bobSellOrder.GetStatus()}");
    }

    private static void PrintAccountStatus(User user)
    {
        var portfolio = user.GetAccount().GetPortfolio();
        var portfolioStr = string.Join(", ", portfolio.Select(kvp => $"{kvp.Key}: {kvp.Value}"));
        Console.WriteLine($"Member: {user.GetName()}, Cash: ${user.GetAccount().GetBalance():F2}, Portfolio: {{{portfolioStr}}}");
    }
}