package coffeevendingmachine;

import java.util.Map;

public class Coffee {
    private final String name;
    private final double price;
    private final Map<Ingredient, Integer> recipe;

    public Coffee(String name, double price, Map<Ingredient, Integer> recipe) {
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

    public Map<Ingredient, Integer> getRecipe() {
        return recipe;
    }
}
