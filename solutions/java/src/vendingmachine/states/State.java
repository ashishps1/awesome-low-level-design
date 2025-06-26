package vendingmachine.states;

import vendingmachine.Coin;

public interface State {
    void insertCoin(Coin coin);
    void selectItem(String code);
    void dispense();
    void refund();
}