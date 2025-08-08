package coffeevendingmachine.state;

import coffeevendingmachine.CoffeeVendingMachine;
import coffeevendingmachine.decorator.Coffee;

public class SelectingState implements VendingMachineState {
    @Override
    public void selectCoffee(CoffeeVendingMachine m, Coffee c) {
        System.out.println("Already selected. Please pay or cancel.");
    }

    @Override
    public void insertMoney(CoffeeVendingMachine machine, int amount) {
        machine.setMoneyInserted(machine.getMoneyInserted() + amount);
        System.out.println("Inserted " + amount + ". Total: " + machine.getMoneyInserted());
        if (machine.getMoneyInserted() >= machine.getSelectedCoffee().getPrice()) {
            machine.setState(new PaidState());
        }
    }

    @Override
    public void dispenseCoffee(CoffeeVendingMachine m) {
        System.out.println("Please insert enough money first.");
    }

    @Override public void cancel(CoffeeVendingMachine machine) {
        System.out.println("Transaction cancelled. Refunding " + machine.getMoneyInserted());
        machine.reset();
        machine.setState(new ReadyState());
    }
}
