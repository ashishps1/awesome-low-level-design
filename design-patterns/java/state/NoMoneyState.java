class NoMoneyState implements State {
    @Override
    public void insertDollar(VendingMachine context) {
        System.out.println("Dollar inserted");
        context.setState(new HasMoneyState());
    }

    @Override
    public void ejectMoney(VendingMachine context) {
        System.out.println("No money to return");
    }

    @Override
    public void dispense(VendingMachine context) {
        System.out.println("Payment required");
    }
}