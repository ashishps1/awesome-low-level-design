package coffeevendingmachine;

import java.util.HashMap;
import java.util.Map;

public class CoffeeVendingMachine {
    private static final CoffeeVendingMachine instance = new CoffeeVendingMachine();
    private final Map<String, CoffeeRecipe> recipes = new HashMap<>();
    private final IngredientStore ingredientStore;
    private final Dispenser dispenser;
    private final PaymentProcessor paymentProcessor;

    private CoffeeVendingMachine() {
        this.ingredientStore = new IngredientStore();
        this.dispenser = new Dispenser();
        this.paymentProcessor = new PaymentProcessor();
        // Initialize default recipes
        addDefaultRecipes();
    }

    private void addDefaultRecipes() {
        recipes.put("Espresso", new CoffeeRecipe("Espresso", 2.5, Map.of("Water", 50, "Coffee", 20)));
        recipes.put("Latte", new CoffeeRecipe("Latte", 3.0, Map.of("Water", 50, "Coffee", 20, "Milk", 30)));
        recipes.put("Cappuccino", new CoffeeRecipe("Cappuccino", 3.5, Map.of("Water", 50, "Coffee", 20, "Milk", 40)));
    }

    private void addRecipe(String name, double price, Map<String, Integer> recipe) {
        recipes.put(name, new CoffeeRecipe(name, price, recipe));
    }

    public static CoffeeVendingMachine getInstance() {
        return instance;
    }

    public void displayMenu() {
        System.out.println("Coffee Menu:");
        for (String recipe : recipes.keySet()) {
            System.out.println(recipe + " - $" + recipes.get(recipe).getPrice());
        }
    }

    public synchronized CoffeeRecipe selectCoffee(String coffeeName) {
        if (!recipes.containsKey(coffeeName)) {
            throw new RuntimeException("Invalid coffee recipe: " + coffeeName);
        }

        return recipes.get(coffeeName);
    }

    public synchronized void dispenseCoffee(CoffeeRecipe coffeeRecipe, Payment payment) {
        if(payment.getAmount() < coffeeRecipe.getPrice()) {
            throw new RuntimeException("Insufficient payment for " + coffeeRecipe.getName() + ". Required: " + coffeeRecipe.getPrice());
        }

        if(!ingredientStore.hasEnoughIngredient(coffeeRecipe.getRecipe())) {
            throw new RuntimeException("Insufficient ingredients to make " + coffeeRecipe.getName());
        }

        ingredientStore.consume(coffeeRecipe.getRecipe());
        dispenser.prepareDrink(coffeeRecipe);

        double change = paymentProcessor.process(coffeeRecipe.getPrice(), payment.getAmount());
        if (change > 0) {
            System.out.println("Please collect your change: $" + change);
        }
    }

    public void refillIngredient(String ingredient, int quantity) {
        ingredientStore.refill(ingredient, quantity);
    }

    public void showIngredients() {
        System.out.println("Ingredient Levels:");
        ingredientStore.getAllIngredients().forEach((k, v) -> System.out.println(k + ": " + v));
    }
}
