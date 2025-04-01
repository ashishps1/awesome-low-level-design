// Abstract class in Template Pattern
class Food {
  prepareFood() {
    this.boilWater();
    this.brew();
    this.pourInCup();
    this.addCondiments();
    this.noNeedVegetables(); // Setting as optional from template pattern
  }

  boilWater() {
    console.log("Boiling the water...");
  }
  brew() {
    throw new error("Method 'brew()' must be implemented");
  }

  pourInCup() {
    console.log("Pouring into cup...");
  }
  addCondiments() {
    throw new error("Method 'addCondiments()' must be implemented");
  }

  // private method
  noNeedVegetables() {
    if (this.shouldAddVegetables()) {
      this.addVegetables();
    }
  }

  addVegetables() {
    console.log("No vegetables added here!");
  }

  // Default is set to false
  shouldAddVegetables() {
    return false;
  }
}

module.exports = Food;
