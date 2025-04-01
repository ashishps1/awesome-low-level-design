class Pizza {
  prepare() {
    throw new error('Method "prepare()" must be implemented');
  }
  bake() {
    console.log("Baking for 25 minutes");
  }
  cut() {
    console.log("Cutting the pizza");
  }
  box() {
    console.log("boxing the pizza");
  }
}

class cheesePizza extends Pizza {
  prepare() {
    console.log("Preparing cheese pizza");
  }
}

class pepperoniPizza extends Pizza {
  prepare() {
    console.log("Preparing pepperoni pizza");
  }
}

module.exports = {
  cheesePizza,
  pepperoniPizza,
};
