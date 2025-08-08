package hotelmanagementsystem.decorator;

public abstract class AmenityDecorator implements Bookable {
    protected Bookable bookable;

    public AmenityDecorator(Bookable bookable) {
        this.bookable = bookable;
    }

    @Override
    public double getCost() {
        return bookable.getCost();
    }

    @Override
    public String getDescription() {
        return bookable.getDescription();
    }
}
