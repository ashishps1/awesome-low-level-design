package vendingmachine.states;

import vendingmachine.Coin;
import vendingmachine.VendingMachine;

public abstract class State {
    VendingMachine machine;

    State(VendingMachine machine) {
        this.machine = machine;
    }

    public abstract void insertCoin(Coin coin);
    public abstract void selectItem(String code);
    public abstract void dispense();
    public abstract void refund();
}