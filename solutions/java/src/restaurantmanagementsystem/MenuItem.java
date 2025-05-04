package restaurantmanagementsystem;

public class MenuItem {
    private final String name;
    private final double price;
    private final boolean available;

    public MenuItem(String name, double price) {
        this.name = name;
        this.price = price;
        this.available = true;
    }

    public String getName() {
        return name;
    }

    public double getPrice() {
        return price;
    }

    public boolean isAvailable() {
        return available;
    }
}
