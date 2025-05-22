public class VendingMachineNaive {
    private enum State {
        IDLE,
        ITEM_SELECTED,
        HAS_MONEY,
        DISPENSING
    }

    private State currentState = State.IDLE;
    private String selectedItem = "";
    private double insertedAmount = 0.0;

    public void selectItem(String itemCode) {
        switch (currentState) {
            case IDLE:
                selectedItem = itemCode;
                System.out.println("Item '" + itemCode + "' selected. Please insert coin.");
                currentState = State.ITEM_SELECTED;
                break;
            case ITEM_SELECTED:
                System.out.println("Item already selected: '" + selectedItem + "'. Insert coin or cancel.");
                break;
            case HAS_MONEY:
                System.out.println("Payment already received for item '" + selectedItem + "'. Dispense in progress.");
                break;
            case DISPENSING:
                System.out.println("Cannot select new item. Currently dispensing.");
                break;
        }
    }

    public void insertCoin(double amount) {
        switch (currentState) {
            case IDLE:
                System.out.println("No item selected. Please select an item before inserting coins.");
                break;
            case ITEM_SELECTED:
                insertedAmount = amount;
                System.out.println("Inserted $" + amount + " for item '" + selectedItem + "'. Ready to dispense.");
                currentState = State.HAS_MONEY;
                break;
            case HAS_MONEY:
                System.out.println("Money already inserted. Please wait or press dispense.");
                break;
            case DISPENSING:
                System.out.println("Currently dispensing. Please wait.");
                break;
        }
    }

    public void dispenseItem() {
        switch (currentState) {
            case IDLE:
                System.out.println("No item selected. Nothing to dispense.");
                break;
            case ITEM_SELECTED:
                System.out.println("Please insert coin before dispensing.");
                break;
            case HAS_MONEY:
                System.out.println("Dispensing item '" + selectedItem + "'...");
                currentState = State.DISPENSING;

                // Simulate delay and completion
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }

                System.out.println("Item dispensed successfully.");
                resetMachine();
                break;
            case DISPENSING:
                System.out.println("Already dispensing. Please wait.");
                break;
        }
    }

    public void cancelTransaction() {
        switch (currentState) {
            case IDLE:
                System.out.println("Nothing to cancel.");
                break;
            case ITEM_SELECTED:
                System.out.println("Transaction cancelled. Returning to IDLE.");
                resetMachine();
                break;
            case HAS_MONEY:
                System.out.println("Transaction cancelled. Refunding $" + insertedAmount + ".");
                resetMachine();
                break;
            case DISPENSING:
                System.out.println("Cannot cancel. Item is being dispensed.");
                break;
        }
    }

    private void resetMachine() {
        selectedItem = "";
        insertedAmount = 0.0;
        currentState = State.IDLE;
    }
}