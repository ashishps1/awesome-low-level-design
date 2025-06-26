package vendingmachine.states;

import vendingmachine.Coin;
import vendingmachine.VendingMachine;

public class HasMoneyState implements State {
    private final VendingMachine machine;

    public HasMoneyState(VendingMachine machine) {
        this.machine = machine;
    }

    @Override
    public void insertCoin(Coin coin) {
        System.out.println("Already received full amount.");
    }

    @Override
    public void selectItem(String code) {
        System.out.println("Item already selected.");
    }

    @Override
    public void dispense() {
        machine.setState(machine.getDispensingState());
        machine.dispenseItem();
    }

    @Override
    public void refund() {
        machine.refundBalance();
        machine.reset();
        machine.setState(machine.getIdleState());
    }
}
