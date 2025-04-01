class VendingMachine {
    private State currentState;

    public VendingMachine() {
        currentState = new NoMoneyState();
    }

    public void setState(State state) {
        this.currentState = state;
    }

    public void insertDollar() {
        currentState.insertDollar(this);
    }

    public void ejectMoney() {
        currentState.ejectMoney(this);
    }

    public void dispense() {
        currentState.dispense(this);
    }
}