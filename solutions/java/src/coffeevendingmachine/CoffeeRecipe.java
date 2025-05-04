package coffeevendingmachine;

import java.util.Map;

public class CoffeeRecipe {
    private final String name;
    private final double price;
    private final Map<String, Integer> recipe;

    public CoffeeRecipe(String name, double price, Map<String, Integer> recipe) {
        this.name = name;
        this.price = price;
        this.recipe = recipe;
    }

    public String getName() {
        return name;
    }

    public double getPrice() {
        return price;
    }

    public Map<String, Integer> getRecipe() {
        return recipe;
    }
}
