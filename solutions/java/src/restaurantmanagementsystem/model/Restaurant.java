package restaurantmanagementsystem.model;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Restaurant {
    private static final Restaurant INSTANCE = new Restaurant();
    private final Map<String, Waiter> waiters = new HashMap<>();
    private final Map<String, Chef> chefs = new HashMap<>();
    private final Map<Integer, Table> tables = new HashMap<>();
    private final Menu menu = new Menu();

    private Restaurant() {}

    public static Restaurant getInstance() {
        return INSTANCE;
    }

    public void addWaiter(Waiter waiter) { waiters.put(waiter.getId(), waiter); }
    public Waiter getWaiter(String id) { return waiters.get(id); }

    public void addChef(Chef chef) { chefs.put(chef.getId(), chef); }
    public Chef getChef(String id) { return chefs.get(id); }

    public List<Chef> getChefs() {
        return chefs.values().stream().toList();
    }

    public List<Waiter> getWaiters() {
        return waiters.values().stream().toList();
    }

    public void addTable(Table table) { tables.put(table.getId(), table); }

    public Menu getMenu() { return menu; }
}