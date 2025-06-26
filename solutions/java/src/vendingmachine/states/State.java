package vendingmachine.states;

import vendingmachine.Coin;

public interface State {
    void selectItem(String code);

    void insertCoin(Coin coin);

    void dispense();

    void returnChange();
}