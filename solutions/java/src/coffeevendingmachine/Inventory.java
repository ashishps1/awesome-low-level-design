package coffeevendingmachine;

import coffeevendingmachine.enums.Ingredient;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class Inventory {
    private static final Inventory INSTANCE = new Inventory();
    private final Map<Ingredient, Integer> stock = new ConcurrentHashMap<>();

    private Inventory() {
        // Private constructor to prevent instantiation
    }

    public static Inventory getInstance() {
        return INSTANCE;
    }

    public void addStock(Ingredient ingredient, int quantity) {
        stock.put(ingredient, stock.getOrDefault(ingredient, 0) + quantity);
    }

    public boolean hasIngredients(Map<Ingredient, Integer> recipe) {
        return recipe.entrySet().stream()
                .allMatch(entry -> stock.getOrDefault(entry.getKey(), 0) >= entry.getValue());
    }

    public synchronized void deductIngredients(Map<Ingredient, Integer> recipe) {
        if (!hasIngredients(recipe)) {
            System.err.println("Not enough ingredients to make coffee.");
            return;
        }
        recipe.forEach((ingredient, quantity) ->
                stock.put(ingredient, stock.get(ingredient) - quantity));
    }

    public void printInventory() {
        System.out.println("--- Current Inventory ---");
        stock.forEach((key, value) -> System.out.println(key + ": " + value));
        System.out.println("-------------------------");
    }
}