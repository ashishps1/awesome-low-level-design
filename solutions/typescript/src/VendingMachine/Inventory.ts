import Item from "./Item";

export default class Inventory {
  private itemMap: Map<string, Item>;
  private stockMap: Map<string, number>;

  constructor() {
    this.itemMap = new Map();
    this.stockMap = new Map();
  }

  addItem(code: string, item: Item, quantity: number) {
    this.itemMap.set(code, item);
    this.stockMap.set(code, quantity);
  }

  getItem(code: string) {
    return this.itemMap.get(code);
  }

  isAvailable(code: string) {
    return (this.stockMap.get(code) ?? 0) > 0;
  }

  reduceStock(code: string) {
    const stock = this.stockMap.get(code);
    if (!stock || stock == 0) throw new Error("No Stock");

    this.stockMap.set(code, stock - 1);
  }
}
