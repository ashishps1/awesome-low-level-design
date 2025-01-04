const Coffee = require("./coffee");
const {Cream, Sugar, Ice} = require("./additional");

// Create an instance of coffee
let myCoffee = new Coffee();
console.log(`Base amount: ${myCoffee.cost()}`); // Get base cost of coffee

myCoffee = new Sugar(myCoffee);
console.log(`Sugar amount: ${myCoffee.cost()}`); // Add cost of sugar

myCoffee = new Cream(myCoffee);
console.log(`Cream amount: ${myCoffee.cost()}`); // Add cost of cream

myCoffee = new Ice(myCoffee);
console.log(`Ice amount: ${myCoffee.cost()}`); // Add cost of ice


