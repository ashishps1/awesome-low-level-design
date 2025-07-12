import { Coin } from "./Coin";
import VendingMachine from "./VendingMachine";

export default class VendingMachineDemo{
  static run(){
    const vendingMachine = VendingMachine.getInstance();

    // Add products to the inventory
    vendingMachine.addItem("A1", "Coke", 25, 3);
    vendingMachine.addItem("A2", "Pepsi", 25, 2);
    vendingMachine.addItem("B1", "Water", 10, 5);

    // Select a product
    console.log("\n--- Step 1: Select an item ---");
    vendingMachine.selectItem("A1");

    // Insert coins
    console.log("\n--- Step 2: Insert coins ---");
    vendingMachine.insertCoin(Coin.DIME); // 10
    vendingMachine.insertCoin(Coin.DIME); // 10
    vendingMachine.insertCoin(Coin.NICKEL); // 5

    // Dispense the product
    console.log("\n--- Step 3: Dispense item ---");
    vendingMachine.dispense(); // Should dispense Coke

    // Select another item
    console.log("\n--- Step 4: Select another item ---");
    vendingMachine.selectItem("B1");

    // Insert more amount
    console.log("\n--- Step 5: Insert more than needed ---");
    vendingMachine.insertCoin(Coin.QUARTER); // 25

    // Try to dispense the product
    console.log("\n--- Step 6: Dispense and return change ---");
    vendingMachine.dispense();
  }
}
