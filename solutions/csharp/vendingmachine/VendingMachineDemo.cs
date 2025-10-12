using System;
using System.Collections.Generic;

public class VendingMachineDemo
{
    public static void Main()
    {
        VendingMachine vendingMachine = VendingMachine.GetInstance();

        // Add products to the inventory
        vendingMachine.AddItem("A1", "Coke", 25, 3);
        vendingMachine.AddItem("A2", "Pepsi", 25, 2);
        vendingMachine.AddItem("B1", "Water", 10, 5);

        // Select a product
        Console.WriteLine("\n--- Step 1: Select an item ---");
        vendingMachine.SelectItem("A1");

        // Insert coins
        Console.WriteLine("\n--- Step 2: Insert coins ---");
        vendingMachine.InsertCoin(Coin.DIME); // 10
        vendingMachine.InsertCoin(Coin.DIME); // 10
        vendingMachine.InsertCoin(Coin.NICKEL); // 5

        // Dispense the product
        Console.WriteLine("\n--- Step 3: Dispense item ---");
        vendingMachine.Dispense(); // Should dispense Coke

        // Select another item
        Console.WriteLine("\n--- Step 4: Select another item ---");
        vendingMachine.SelectItem("B1");

        // Insert more amount
        Console.WriteLine("\n--- Step 5: Insert more than needed ---");
        vendingMachine.InsertCoin(Coin.QUARTER); // 25

        // Try to dispense the product
        Console.WriteLine("\n--- Step 6: Dispense and return change ---");
        vendingMachine.Dispense();
    }
}