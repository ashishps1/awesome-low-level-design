package coffeevendingmachine.state;

import coffeevendingmachine.CoffeeVendingMachine;
import coffeevendingmachine.Inventory;
import coffeevendingmachine.decorator.Coffee;

public class PaidState implements VendingMachineState {
    @Override
    public void selectCoffee(CoffeeVendingMachine m, Coffee c) {
        System.out.println("Cannot select another coffee now.");
    }

    @Override
    public void insertMoney(CoffeeVendingMachine m, int a) {
        System.out.println("Already paid. Please wait for your coffee.");
    }

    @Override
    public void dispenseCoffee(CoffeeVendingMachine machine) {
        Inventory inventory = Inventory.getInstance();
        Coffee coffeeToDispense = machine.getSelectedCoffee();

        if (!inventory.hasIngredients(machine.getSelectedCoffee().getRecipe())) {
            System.out.println("Sorry, out of ingredients for " + machine.getSelectedCoffee().getCoffeeType());
            machine.setState(new OutOfIngredientState());
            machine.getState().cancel(machine);
            return;
        }
        inventory.deductIngredients(machine.getSelectedCoffee().getRecipe());

        coffeeToDispense.prepare();

        int change = machine.getMoneyInserted() - machine.getSelectedCoffee().getPrice();
        if (change > 0)
            System.out.println("Returning change: " + change);

        machine.reset();
        machine.setState(new ReadyState());
    }

    @Override
    public void cancel(CoffeeVendingMachine m) {
        new SelectingState().cancel(m); // Same as in SelectingState
    }
}
