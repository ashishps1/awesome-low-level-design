import CoffeeVendingMachine from "./CoffeeVendingMachine";
import Payment from "./Payment";

export default class CoffeeVendingMachineDemo {
  static run() {
    const coffeeVendingMachine = CoffeeVendingMachine.getInstance();

    coffeeVendingMachine.refillIngredient("Water", 120);
    coffeeVendingMachine.refillIngredient("Milk", 70);
    coffeeVendingMachine.refillIngredient("Coffee", 150);

    coffeeVendingMachine.displayMenu();

    const espresso = coffeeVendingMachine.selectCoffee("Espresso");
    coffeeVendingMachine.dispenseCoffee(espresso, new Payment(3.0));

    const cappuccino = coffeeVendingMachine.selectCoffee("Cappuccino");
    coffeeVendingMachine.dispenseCoffee(cappuccino, new Payment(3.5));

    const latte = coffeeVendingMachine.selectCoffee("Latte");
    coffeeVendingMachine.dispenseCoffee(latte, new Payment(4.0));
  }
}
