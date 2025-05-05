package vendingmachine;

class IdleState implements VendingMachineState {
    private final VendingMachine vendingMachine;

    public IdleState(VendingMachine vendingMachine) {
        this.vendingMachine = vendingMachine;
    }

    @Override
    public void selectProduct(Product product) {
        if (vendingMachine.getInventory().isAvailable(product)) {
            System.out.println("Product selected: " + product.getName());
            vendingMachine.setSelectedProduct(product);
            vendingMachine.setState(vendingMachine.getReadyState());
        } else {
            System.out.println("Product not available: " + product.getName());
        }
    }

    @Override
    public void insertCoin(Coin coin) {
        System.out.println("Please select a product first.");
    }

    @Override
    public void insertNote(Note note) {
        System.out.println("Please select a product first.");
    }

    @Override
    public void dispenseProduct() {
        System.out.println("Please select a product and make payment.");
    }

    @Override
    public void returnChange() {
        System.out.println("No change to return.");
    }
}
