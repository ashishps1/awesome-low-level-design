package hotelmanagementsystem.decorator;

public class SpaDecorator extends AmenityDecorator {
    private static final double SPA_COST = 50.0;

    public SpaDecorator(Bookable bookable) {
        super(bookable);
    }

    @Override
    public double getCost() {
        return super.getCost() + SPA_COST;
    }



    @Override
    public String getDescription() {
        return super.getDescription() + " with Spa Access";
    }
}
