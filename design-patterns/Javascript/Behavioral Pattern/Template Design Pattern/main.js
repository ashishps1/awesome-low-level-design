const { Tea, Coffee } = require("./beveragesTypes");

// Meal 1
console.log("Preparing Tea..");
const tea = new Tea();
tea.prepareFood();
console.log(""); // For spacing

// Meal 2
console.log("Preparing Coffee..");
const coffee = new Coffee();
coffee.prepareFood();
