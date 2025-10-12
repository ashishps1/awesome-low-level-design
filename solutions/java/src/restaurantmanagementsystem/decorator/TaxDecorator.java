package restaurantmanagementsystem.decorator;

public class TaxDecorator extends BillDecorator {
    private final double taxRate;

    public TaxDecorator(BillComponent component, double taxRate) {
        super(component);
        this.taxRate = taxRate;
    }

    @Override
    public double calculateTotal() {
        return super.calculateTotal() * (1 + taxRate);
    }

    @Override
    public String getDescription() {
        return super.getDescription() + ", Tax @" + (taxRate * 100) + "%";
    }
}