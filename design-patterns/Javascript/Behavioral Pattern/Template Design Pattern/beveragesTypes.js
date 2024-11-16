// Concrete classes for Food
// Make using of superClasses from templatePattern and modifying here (subClasses)

const Food = require("./beverages");

class Tea extends Food {
  brew() {
    console.log("Steeping the tea...");
  }

  addCondiments() {
    console.log("Adding lemon...");
  }

  addVegetables() {
    console.log("Adding mint leaves to tea...");
  }

  shouldAddVegetables() {
    return true; // Tea includes vegetables
  }
}

class Coffee extends Food {
  brew() {
    console.log("Dripping coffee through filter...");
  }

  addCondiments() {
    console.log("Adding sugar and milk...");
  }
}

module.exports = { Tea, Coffee };
