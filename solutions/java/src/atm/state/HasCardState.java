package atm.state;

import atm.ATM;
import atm.OperationType;

public class HasCardState implements ATMState {
    @Override
    public void insertCard(ATM atm, String cardNumber) {
        System.out.println("Error: A card is already inserted. Cannot insert another card.");
    }

    @Override
    public void enterPin(ATM atm, String pin) {
        System.out.println("Authenticating PIN...");
        boolean isAuthenticated = atm.authenticate(pin);;

        if (isAuthenticated) {
            System.out.println("Authentication successful.");
            atm.changeState(new AuthenticatedState());
        } else {
            System.out.println("Authentication failed: Incorrect PIN.");
            ejectCard(atm);
        }
    }

    @Override
    public void selectOperation(ATM atm, OperationType op, int... args) {
        System.out.println("Error: Please enter your PIN first to select an operation.");
    }

    @Override
    public void ejectCard(ATM atm) {
        System.out.println("Card has been ejected. Thank you for using our ATM.");
        atm.setCurrentCard(null);
        atm.changeState(new IdleState());
    }
}
