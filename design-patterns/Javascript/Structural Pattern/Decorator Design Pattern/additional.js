// Additional behavior class

class Cream {
  constructor(coffee) {
    this.coffee = coffee;
  }

  cost() {
    return this.coffee.cost() + 5; // Add cost of cream to the base coffee class
  }
}

class Sugar {
  constructor(coffee) {
    this.coffee = coffee; // Store the coffee instance
  }

  cost() {
    return this.coffee.cost() + 2; // Add cost of sugar to the base coffee class
  }
}

class Ice{
  constructor(coffee) {
    this.coffee = coffee; // Store the coffee instance
  }

  cost() {
    return this.coffee.cost() + 1; // Add cost of ice to the base coffee class
  }
}


module.exports = {Cream, Sugar, Ice};
