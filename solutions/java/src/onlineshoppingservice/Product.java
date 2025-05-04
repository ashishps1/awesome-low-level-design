package onlineshoppingservice;

import java.util.UUID;

public class Product {
    private final String id;
    private final String name;
    private final String description;
    private final double price;
    private int stock;

    public Product(String name, String description, double price, int stock) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.description = description;
        this.price = price;
        this.stock = stock;
    }

    public synchronized void increaseStock(int quantity) {
        stock += quantity;
    }

    public synchronized void decreaseStock(int quantity) {
        if (stock < quantity) throw new IllegalStateException("Insufficient stock");
        stock -= quantity;
    }

    public synchronized void updateQuantity(int quantity) {
        this.stock += quantity;
    }

    public synchronized boolean isAvailable(int quantity) {
        return this.stock >= quantity;
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

    public int getStock() {
        return stock;
    }
}
