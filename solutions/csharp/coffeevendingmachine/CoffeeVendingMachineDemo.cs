using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

public class CoffeeVendingMachineDemo
{
    public static void Main(string[] args)
    {
        CoffeeVendingMachine machine = CoffeeVendingMachine.GetInstance();
        Inventory inventory = Inventory.GetInstance();

        // Initial setup: Refill inventory
        Console.WriteLine("=== Initializing Vending Machine ===");
        inventory.AddStock(Ingredient.COFFEE_BEANS, 50);
        inventory.AddStock(Ingredient.WATER, 500);
        inventory.AddStock(Ingredient.MILK, 200);
        inventory.AddStock(Ingredient.SUGAR, 100);
        inventory.AddStock(Ingredient.CARAMEL_SYRUP, 50);
        inventory.PrintInventory();

        // Scenario 1: Successful Purchase of a Latte
        Console.WriteLine("\n--- SCENARIO 1: Buy a Latte (Success) ---");
        machine.SelectCoffee(CoffeeType.LATTE, new List<ToppingType>());
        machine.InsertMoney(200);
        machine.InsertMoney(50); // Total 250, price is 220
        machine.DispenseCoffee();
        inventory.PrintInventory();

        // Scenario 2: Purchase with Insufficient Funds & Cancellation
        Console.WriteLine("\n--- SCENARIO 2: Buy Espresso (Insufficient Funds & Cancel) ---");
        machine.SelectCoffee(CoffeeType.ESPRESSO, new List<ToppingType>());
        machine.InsertMoney(100); // Price is 150
        machine.DispenseCoffee(); // Should fail
        machine.Cancel(); // Should refund 100
        inventory.PrintInventory(); // Should be unchanged

        // Scenario 3: Attempt to Buy with Insufficient Ingredients
        Console.WriteLine("\n--- SCENARIO 3: Buy Cappuccino (Out of Milk) ---");
        inventory.PrintInventory();
        machine.SelectCoffee(CoffeeType.CAPPUCCINO, new List<ToppingType> { ToppingType.CARAMEL_SYRUP, ToppingType.EXTRA_SUGAR });
        machine.InsertMoney(300);
        machine.DispenseCoffee(); // Should fail and refund
        inventory.PrintInventory();

        // Refill and final test
        Console.WriteLine("\n--- REFILLING AND FINAL TEST ---");
        inventory.AddStock(Ingredient.MILK, 200);
        inventory.PrintInventory();
        machine.SelectCoffee(CoffeeType.LATTE, new List<ToppingType> { ToppingType.CARAMEL_SYRUP });
        machine.InsertMoney(250);
        machine.DispenseCoffee();
        inventory.PrintInventory();
    }
}