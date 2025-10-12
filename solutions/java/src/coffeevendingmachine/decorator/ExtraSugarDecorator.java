package coffeevendingmachine.decorator;

import coffeevendingmachine.enums.Ingredient;

import java.util.HashMap;
import java.util.Map;

public class ExtraSugarDecorator extends CoffeeDecorator {
    private static final int COST = 10;
    private static final Map<Ingredient, Integer> RECIPE_ADDITION = Map.of(Ingredient.SUGAR, 1);

    public ExtraSugarDecorator(Coffee coffee) {
        super(coffee);
    }

    @Override
    public String getCoffeeType() {
        return decoratedCoffee.getCoffeeType() + ", Extra Sugar";
    }

    @Override
    public int getPrice() {
        return decoratedCoffee.getPrice() + COST;
    }

    @Override
    public Map<Ingredient, Integer> getRecipe() {
        // Merge the recipes
        Map<Ingredient, Integer> newRecipe = new HashMap<>(decoratedCoffee.getRecipe());
        RECIPE_ADDITION.forEach((ingredient, qty) ->
                newRecipe.merge(ingredient, qty, Integer::sum));
        return newRecipe;
    }

    @Override
    public void prepare() {
        super.prepare();
        System.out.println("- Stirring in Extra Sugar.");
    }
}
