package coffeevendingmachine.decorator;

import coffeevendingmachine.enums.Ingredient;

import java.util.HashMap;
import java.util.Map;

public class CaramelSyrupDecorator extends CoffeeDecorator {
    private static final int COST = 30;
    private static final Map<Ingredient, Integer> RECIPE_ADDITION = Map.of(Ingredient.CARAMEL_SYRUP, 10);

    public CaramelSyrupDecorator(Coffee coffee) {
        super(coffee);
    }

    @Override
    public String getCoffeeType() {
        return decoratedCoffee.getCoffeeType() + ", Caramel Syrup";
    }

    @Override
    public int getPrice() {
        return decoratedCoffee.getPrice() + COST;
    }

    @Override
    public Map<Ingredient, Integer> getRecipe() {
        Map<Ingredient, Integer> newRecipe = new HashMap<>(decoratedCoffee.getRecipe());
        RECIPE_ADDITION.forEach((ingredient, qty) ->
                newRecipe.merge(ingredient, qty, Integer::sum));
        return newRecipe;
    }

    @Override
    public void prepare() {
        // First, prepare the underlying coffee (e.g., the Latte with Sugar)
        super.prepare();
        // Then, add the specific step for this decorator
        System.out.println("- Drizzling Caramel Syrup on top.");
    }
}
