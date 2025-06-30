package atm.state;

import atm.ATM;
import atm.OperationType;

public class AuthenticatedState implements ATMState {
    @Override
    public void insertCard(ATM atm, String cardNumber) {
        System.out.println("Error: A card is already inserted and a session is active.");
    }

    @Override
    public void enterPin(ATM atm, String pin) {
        System.out.println("Error: PIN has already been entered and authenticated.");
    }

    @Override
    public void selectOperation(ATM atm, OperationType op, int... args) {
        // In a real UI, this would be a menu. Here we use a switch.
        switch (op) {
            case CHECK_BALANCE:
                atm.checkBalance();
                break;

            case WITHDRAW_CASH:
                if (args.length == 0 || args[0] <= 0) {
                    System.out.println("Error: Invalid withdrawal amount specified.");
                    break;
                }
                int amountToWithdraw = args[0];

                double accountBalance = atm.getBankService().getBalance(atm.getCurrentCard());

                if (amountToWithdraw > accountBalance) {
                    System.out.println("Error: Insufficient balance.");
                    break;
                }

                System.out.println("Processing withdrawal for $" + amountToWithdraw);
                // Delegate the complex withdrawal logic to the ATM's dedicated method
                atm.withdrawCash(amountToWithdraw);
                break;

            case DEPOSIT_CASH:
                if (args.length == 0 || args[0] <= 0) {
                    System.out.println("Error: Invalid withdrawal amount specified.");
                    break;
                }
                int amountToDeposit = args[0];
                System.out.println("Processing deposit for $" + amountToDeposit);
                atm.depositCash(amountToDeposit);
                break;

            default:
                System.out.println("Error: Invalid operation selected.");
                break;
        }

        // End the session after one transaction
        System.out.println("Transaction complete.");
        ejectCard(atm);
    }

    @Override
    public void ejectCard(ATM atm) {
        System.out.println("Ending session. Card has been ejected. Thank you for using our ATM.");
        atm.setCurrentCard(null);
        atm.changeState(new IdleState());
    }
}
