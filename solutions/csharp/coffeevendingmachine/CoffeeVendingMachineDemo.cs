using System;

namespace CoffeeVendingMachine
{
    public class CoffeeVendingMachineDemo
    {
        public static void Run()
        {
            CoffeeMachine coffeeMachine = CoffeeMachine.Instance;

            // Display coffee menu
            coffeeMachine.DisplayMenu();

            // Simulate user requests
            Coffee espresso = coffeeMachine.SelectCoffee("Espresso");
            coffeeMachine.DispenseCoffee(espresso, new Payment(3.0));

            Coffee cappuccino = coffeeMachine.SelectCoffee("Cappuccino");
            coffeeMachine.DispenseCoffee(cappuccino, new Payment(3.5));

            Coffee latte = coffeeMachine.SelectCoffee("Latte");
            coffeeMachine.DispenseCoffee(latte, new Payment(4.0));
        }
    }
}