package vendingmachine.states;

import vendingmachine.Coin;
import vendingmachine.VendingMachine;

public class ItemSelectedState implements State {
    private final VendingMachine machine;

    public ItemSelectedState(VendingMachine machine) {
        this.machine = machine;
    }

    @Override
    public void insertCoin(Coin coin) {
        machine.addBalance(coin.getValue());
        int price = machine.getSelectedItem().getPrice();
        if (machine.getBalance() >= price) {
            machine.setState(machine.getHasMoneyState());
        }
    }

    @Override
    public void selectItem(String code) {
        System.out.println("Item already selected.");
    }

    @Override
    public void dispense() {
        System.out.println("Please insert sufficient money.");
    }

    @Override
    public void returnChange() {
        machine.reset();
        machine.setState(machine.getIdleState());
    }
}
