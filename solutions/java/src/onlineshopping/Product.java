package onlineshopping;

public class Product {
    private final String id;
    private final String name;
    private final String description;
    private final double price;
    private int quantity;

    public Product(String id, String name, String description, double price, int quantity) {
        this.id = id;
        this.name = name;
        this.description = description;
        this.price = price;
        this.quantity = quantity;
    }

    public synchronized void updateQuantity(int quantity) {
        this.quantity += quantity;
    }

    public synchronized boolean isAvailable(int quantity) {
        return this.quantity >= quantity;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    public double getPrice() {
        return price;
    }

    public int getQuantity() {
        return quantity;
    }
}
