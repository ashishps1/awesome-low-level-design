const { cheesePizza, pepperoniPizza } = require("./pizza");

class pizzaFactory {
  static createPizza(pizzaType) {
    if (pizzaType === "cheese") {
      return new cheesePizza();
    } else if (pizzaType === "pepperoni") {
      return new pepperoniPizza();
    } else {
      throw new Error("Invalid pizza type");
    }
  }
}

module.exports = pizzaFactory;
