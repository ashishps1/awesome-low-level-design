package coffeevendingmachine;

public class Dispenser {
    public void prepareDrink(CoffeeRecipe recipe) {
        System.out.println("Dispensing: " + recipe.getName());
    }
}
