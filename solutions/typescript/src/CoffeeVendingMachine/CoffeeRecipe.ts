class CoffeeRecipe {
  private name: string;
  private price: number;
  private recipe: Map<string, number>;

  constructor(name: string, price: number, recipe: Map<string, number>) {
    this.name = name;
    this.price = price;
    this.recipe = recipe;
  }

  public getName(): string {
    return this.name;
  }

  public getPrice(): number {
    return this.price;
  }

  public getRecipe() {
    return this.recipe;
  }
}
export default CoffeeRecipe;
