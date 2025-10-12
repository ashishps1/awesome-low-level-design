package restaurantmanagementsystem.decorator;

public class Bill {
    private final BillComponent component;

    public Bill(BillComponent component) {
        this.component = component;
    }

    public void printBill() {
        System.out.println("\n--- BILL ---");
        System.out.printf("Description: %s\n", component.getDescription());
        System.out.printf("Total: $%.2f\n", component.calculateTotal());
        System.out.println("------------");
    }
}