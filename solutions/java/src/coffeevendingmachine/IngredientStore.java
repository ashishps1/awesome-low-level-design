package coffeevendingmachine;

import java.util.HashMap;
import java.util.Map;

public class IngredientStore {
    private final Map<String, Integer> inventory = new HashMap<>();

    public synchronized void refill(String ingredient, int quantity) {
        inventory.put(ingredient, inventory.getOrDefault(ingredient, 0) + quantity);
    }

    public boolean hasEnoughIngredient(Map<String, Integer> required) {
        for (Map.Entry<String, Integer> entry : required.entrySet()) {
            String ingredient = entry.getKey();
            int available = inventory.getOrDefault(ingredient, 0);
            if (available < entry.getValue()) {
                return false;
            }
        }
        return true;
    }

    public synchronized void consume(Map<String, Integer> required) {
        // deduct ingredient
        for (Map.Entry<String, Integer> entry : required.entrySet()) {
            String ingredient = entry.getKey();
            inventory.put(ingredient, inventory.get(ingredient) - entry.getValue());
        }
    }

    public synchronized int getLevel(String ingredient) {
        return inventory.getOrDefault(ingredient, 0);
    }

    public synchronized Map<String, Integer> getAllIngredients() {
        return new HashMap<>(inventory);
    }
}