import CoffeeRecipe from "./CoffeeRecipe";
import Dispenser from "./Dispenser";
import IngredientStore from "./IngredientStore";
import Payment from "./Payment";
import PaymentProcessor from "./PaymentProcessor";

class CoffeeVendingMachine {
  private static instance: CoffeeVendingMachine | null;
  private recipes: Map<string, CoffeeRecipe>;
  private ingredientStore: IngredientStore;
  private dispenser: Dispenser;
  private paymentProcessor: PaymentProcessor;

  private constructor() {
    this.ingredientStore = new IngredientStore();
    this.dispenser = new Dispenser();
    this.paymentProcessor = new PaymentProcessor();
    this.recipes = new Map();
    this.addDefaultRecipes();
  }

  private addDefaultRecipes(): void {
    this.recipes.set(
      "Latte",
      new CoffeeRecipe(
        "Latte",
        3.0,
        new Map([
          ["Water", 50],
          ["Coffee", 20],
          ["Milk", 30],
        ]),
      ),
    );
    this.recipes.set(
      "Espresso",
      new CoffeeRecipe(
        "Espresso",
        3.5,
        new Map([
          ["Water", 50],
          ["Coffee", 20],
        ]),
      ),
    );
    this.recipes.set(
      "Cappuccino",
      new CoffeeRecipe(
        "Cappuccino",
        3.5,
        new Map([
          ["Water", 50],
          ["Coffee", 20],
          ["Milk", 40],
        ]),
      ),
    );
  }

  public static getInstance(): CoffeeVendingMachine {
    if (!CoffeeVendingMachine.instance) {
      CoffeeVendingMachine.instance = new CoffeeVendingMachine();
    }
    return CoffeeVendingMachine.instance;
  }

  public displayMenu(): void {
    console.log("Coffee Menu:");
    for (const recipe of this.recipes.keys()) {
        console.log(recipe + " - $" + this.recipes.get(recipe)?.getPrice());
    }
  }

  public selectCoffee(coffeeName: string): CoffeeRecipe {
    const recipe = this.recipes.get(coffeeName);
    if (!recipe) throw new Error(`Invalid coffee recipe: ${coffeeName}`);
    console.log('Selected Coffee : ',coffeeName)
    return recipe;
  }

  public dispenseCoffee(recipe: CoffeeRecipe, payment: Payment): void {
    if (payment.getAmount() < recipe.getPrice()) {
      console.error(
        `Insufficient payment for ${recipe.getName()}. Required: ${recipe.getPrice()}`,
      );
      return;
    }

    if (!this.ingredientStore.hasEnoughIngredient(recipe.getRecipe())) {
      console.error(`Insufficient ingredients to make ${recipe.getName()}`);
      return;
    }

    this.ingredientStore.consume(recipe.getRecipe());
    this.dispenser.prepareDrink(recipe);

    const change = this.paymentProcessor.process(
      recipe.getPrice(),
      payment.getAmount(),
    );
    if (change > 0) {
      console.log(`Please collect your change: $${change}`);
    }
  }

  public refillIngredient(ingredient: string, quantity: number): void {
    this.ingredientStore.refill(ingredient, quantity);
  }

  public showIngredients(): void {
    console.log("Ingredient Levels:");
    const ingredients = this.ingredientStore.getAllIngredients();
    for (const [name, quantity] of Object.entries(ingredients)) {
      console.log(`${name}: ${quantity}`);
    }
  }
}
export default CoffeeVendingMachine;
