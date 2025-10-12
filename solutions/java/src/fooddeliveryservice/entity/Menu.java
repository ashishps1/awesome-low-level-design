package fooddeliveryservice.entity;

import java.util.HashMap;
import java.util.Map;

public class Menu {
    private final Map<String, MenuItem> items = new HashMap<>();

    public void addItem(MenuItem item) {
        items.put(item.getId(), item);
    }

    public MenuItem getItem(String id) { return items.get(id); }

    public Map<String, MenuItem> getItems() { return items; }
}
