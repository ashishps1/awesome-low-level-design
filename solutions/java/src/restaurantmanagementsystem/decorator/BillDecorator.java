package restaurantmanagementsystem.decorator;

public abstract class BillDecorator implements BillComponent {
    protected BillComponent wrapped;

    public BillDecorator(BillComponent component) {
        this.wrapped = component;
    }

    @Override
    public double calculateTotal() {
        return wrapped.calculateTotal();
    }

    @Override
    public String getDescription() {
        return wrapped.getDescription();
    }
}
