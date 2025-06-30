package atm;

public class ATMDemo {
    public static void run() {
        ATM atm = ATM.getInstance();

        // Perform Check Balance operation
        atm.insertCard("1234-5678-9012-3456");
        atm.enterPin("1234");
        atm.selectOperation(OperationType.CHECK_BALANCE); // $1000

        // Perform Withdraw Cash operation
        atm.insertCard("1234-5678-9012-3456");
        atm.enterPin("1234");
        atm.selectOperation(OperationType.WITHDRAW_CASH, 570);

        // Perform Deposit Cash operation
        atm.insertCard("1234-5678-9012-3456");
        atm.enterPin("1234");
        atm.selectOperation(OperationType.DEPOSIT_CASH, 200);

        // Perform Check Balance operation
        atm.insertCard("1234-5678-9012-3456");
        atm.enterPin("1234");
        atm.selectOperation(OperationType.CHECK_BALANCE); // $630

        // Perform Withdraw Cash more than balance
        atm.insertCard("1234-5678-9012-3456");
        atm.enterPin("1234");
        atm.selectOperation(OperationType.WITHDRAW_CASH, 700); // Insufficient balance

        // Insert Incorrect PIN
        atm.insertCard("1234-5678-9012-3456");
        atm.enterPin("3425");
    }
}
