package fooddeliveryservice;

import java.util.UUID;

public class MenuItem {
    private final String id;
    private final String name;
    private final String description;
    private final double price;
    private boolean available;

    public MenuItem(String name, String description, double price) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.description = description;
        this.price = price;
        this.available = true;
    }

    public void setAvailable(boolean available) {
        this.available = available;
    }

    public String getName() {
        return name;
    }

    public String getMenuItem() {
        return "Name: " + name + ", Description: " + description + ", Price: " + price;
    }
}
