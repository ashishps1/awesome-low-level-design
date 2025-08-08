package coffeevendingmachine;

import coffeevendingmachine.enums.CoffeeType;
import coffeevendingmachine.enums.Ingredient;
import coffeevendingmachine.enums.ToppingType;

import java.util.List;

public class CoffeeVendingMachineDemo {
    public static void main(String[] args) {
        CoffeeVendingMachine machine = CoffeeVendingMachine.getInstance();
        Inventory inventory = Inventory.getInstance();

        // --- Initial setup: Refill inventory ---
        System.out.println("=== Initializing Vending Machine ===");
        inventory.addStock(Ingredient.COFFEE_BEANS, 50);
        inventory.addStock(Ingredient.WATER, 500);
        inventory.addStock(Ingredient.MILK, 200);
        inventory.addStock(Ingredient.SUGAR, 100);
        inventory.addStock(Ingredient.CARAMEL_SYRUP, 50);
        inventory.printInventory();

        // --- Scenario 1: Successful Purchase of a Latte ---
        System.out.println("\n--- SCENARIO 1: Buy a Latte (Success) ---");
        machine.selectCoffee(CoffeeType.LATTE, List.of());
        machine.insertMoney(200);
        machine.insertMoney(50); // Total 250, price is 220
        machine.dispenseCoffee();
        inventory.printInventory();

        // --- Scenario 2: Purchase with Insufficient Funds & Cancellation ---
        System.out.println("\n--- SCENARIO 2: Buy Espresso (Insufficient Funds & Cancel) ---");
        machine.selectCoffee(CoffeeType.ESPRESSO, List.of());
        machine.insertMoney(100); // Price is 150
        machine.dispenseCoffee(); // Should fail
        machine.cancel(); // Should refund 100
        inventory.printInventory(); // Should be unchanged

        // --- Scenario 3: Attempt to Buy with Insufficient Ingredients ---
        System.out.println("\n--- SCENARIO 3: Buy Cappuccino (Out of Milk) ---");
        inventory.printInventory();
        machine.selectCoffee(CoffeeType.CAPPUCCINO, List.of(ToppingType.CARAMEL_SYRUP, ToppingType.EXTRA_SUGAR));
        machine.insertMoney(300);
        machine.dispenseCoffee(); // Should fail and refund
        inventory.printInventory();

        // --- Refill and final test ---
        System.out.println("\n--- REFILLING AND FINAL TEST ---");
        inventory.addStock(Ingredient.MILK, 200);
        inventory.printInventory();
        machine.selectCoffee(CoffeeType.LATTE, List.of(ToppingType.CARAMEL_SYRUP));
        machine.insertMoney(250);
        machine.dispenseCoffee();
        inventory.printInventory();
    }
}
