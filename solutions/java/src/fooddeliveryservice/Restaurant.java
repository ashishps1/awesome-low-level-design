package fooddeliveryservice;

import java.util.List;

public class Restaurant {
    private final String id;
    private final String name;
    private final String address;
    private final List<MenuItem> menu;

    public Restaurant(String id, String name, String address, List<MenuItem> menu) {
        this.id = id;
        this.name = name;
        this.address = address;
        this.menu = menu;
    }

    public void addMenuItem(MenuItem item) {
        menu.add(item);
    }

    public void removeMenuItem(MenuItem item) {
        menu.remove(item);
    }

    public String getId() {
        return id;
    }

    public List<MenuItem> getMenu() {
        return menu;
    }
}
