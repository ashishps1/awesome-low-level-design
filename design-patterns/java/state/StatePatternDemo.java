public class StatePatternDemo {
    public static void main(String[] args) {
        VendingMachine vendingMachine = new VendingMachine();

        vendingMachine.insertDollar();
        vendingMachine.dispense();

        System.out.println("----");

        vendingMachine.insertDollar();
        vendingMachine.insertDollar();
        vendingMachine.ejectMoney();
        vendingMachine.dispense();

        System.out.println("----");

        vendingMachine.insertDollar();
        vendingMachine.dispense();
        vendingMachine.ejectMoney();
    }
}