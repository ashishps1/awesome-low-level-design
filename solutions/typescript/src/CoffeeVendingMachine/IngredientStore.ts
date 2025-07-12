class IngredientStore {
  private inventory: Map<string, number>;

  constructor() {
    this.inventory = new Map();
  }

  public refill(ingredient: string, quantity: number): void {
    this.inventory.set(
      ingredient,
      (this.inventory.get(ingredient) || 0) + quantity,
    );
  }

  public hasEnoughIngredient(required: Map<string, number>): boolean {
    for (const [ingredient, quantity] of required) {
      if ((this.inventory.get(ingredient) || 0) < quantity) return false;
    }
    return true;
  }

  public consume(required: Map<string, number>): void {
    for (const [ingredient, quantity] of required) {
      const currentStock = this.inventory.get(ingredient) || 0;
      if (currentStock < quantity) {
        throw new Error(`Not enough ${ingredient} to consume`);
      }
      this.inventory.set(ingredient, currentStock - quantity);
    }
  }

  public getLevel(ingredient: string): number {
    return this.inventory.get(ingredient) || 0;
  }

  public getAllIngredients(): Map<string, number> {
    return { ...this.inventory };
  }
}
export default IngredientStore;
