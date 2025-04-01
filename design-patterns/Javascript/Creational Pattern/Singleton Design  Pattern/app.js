
// Importing
const singleton = require("./singleton");
const Singleton1 = require("./singleton");
const Singleton2 = require("./singleton");

Singleton1.increment();

console.log(Singleton1.getData());
console.log(Singleton2.getData());

console.log(Singleton1 === Singleton2); // True