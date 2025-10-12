package restaurantmanagementsystem.decorator;

public class ServiceChargeDecorator extends BillDecorator {
    private final double serviceCharge;

    public ServiceChargeDecorator(BillComponent component, double charge) {
        super(component);
        this.serviceCharge = charge;
    }

    @Override
    public double calculateTotal() {
        return super.calculateTotal() + serviceCharge;
    }

    @Override
    public String getDescription() {
        return super.getDescription() + ", Service Charge";
    }
}