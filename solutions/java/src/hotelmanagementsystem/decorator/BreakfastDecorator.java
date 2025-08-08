package hotelmanagementsystem.decorator;

public class BreakfastDecorator extends AmenityDecorator {
    private static final double BREAKFAST_COST = 25.0;

    public BreakfastDecorator(Bookable bookable) {
        super(bookable);
    }

    @Override
    public double getCost() {
        return super.getCost() + BREAKFAST_COST;
    }

    @Override
    public String getDescription() {
        return super.getDescription() + " with Breakfast";
    }
}
