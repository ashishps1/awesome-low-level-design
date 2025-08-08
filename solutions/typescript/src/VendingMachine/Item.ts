export default class Item {
  private code: string;
  private name: string;
  private price: number;

  constructor(code: string, name: string, price: number) {
    this.code = code;
    this.name = name;
    this.price = price;
  }

  getName() {
    return this.name;
  }

  getPrice() {
    return this.price;
  }
}
