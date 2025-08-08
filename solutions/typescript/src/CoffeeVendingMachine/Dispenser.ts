import CoffeeRecipe from "./CoffeeRecipe";

class Dispenser {
  public prepareDrink(recipe: CoffeeRecipe): void {
    console.log(`Dispensing: ${recipe.getName()}`);
  }
}
export default Dispenser;