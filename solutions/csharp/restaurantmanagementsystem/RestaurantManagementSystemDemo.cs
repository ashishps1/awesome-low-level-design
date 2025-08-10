using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

public class RestaurantManagementSystemDemo
{
    public static void Main(string[] args)
    {
        Console.WriteLine("=== Initializing Restaurant System ===");
        RestaurantManagementSystemFacade rmsFacade = RestaurantManagementSystemFacade.GetInstance();

        Table table1 = rmsFacade.AddTable(1, 4);
        Chef chef1 = rmsFacade.AddChef("CHEF01", "Gordon");
        Waiter waiter1 = rmsFacade.AddWaiter("W01", "Alice");

        MenuItem pizza = rmsFacade.AddMenuItem("PIZZA01", "Margherita Pizza", 12.50);
        MenuItem pasta = rmsFacade.AddMenuItem("PASTA01", "Carbonara Pasta", 15.00);
        MenuItem coke = rmsFacade.AddMenuItem("DRINK01", "Coke", 2.50);
        Console.WriteLine("Initialization Complete.\n");

        Console.WriteLine("=== SCENARIO 1: Taking an order ===");
        Order order1 = rmsFacade.TakeOrder(table1.GetId(), waiter1.GetId(), 
            new List<string> { pizza.GetId(), coke.GetId() });
        Console.WriteLine($"Order taken successfully. Order ID: {order1.GetOrderId()}");

        Console.WriteLine("\n=== SCENARIO 2: Chef prepares, Waiter gets notified ===");
        rmsFacade.MarkItemsAsReady(order1.GetOrderId());
        rmsFacade.ServeOrder(waiter1.GetId(), order1.GetOrderId());

        Console.WriteLine("\n=== SCENARIO 3: Generating the bill ===");
        Bill finalBill = rmsFacade.GenerateBill(order1.GetOrderId());
        finalBill.PrintBill();
    }
}