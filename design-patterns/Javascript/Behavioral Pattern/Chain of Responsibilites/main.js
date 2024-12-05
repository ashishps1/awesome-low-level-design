const {
  InternetConnectionTeam,
  InternetSupportTeam,
  PhoneConnectionTeam,
  PhoneSupportTeam,
} = require("./supportRequest");


const phoneSupport = new PhoneSupportTeam(null);
const phoneConnection = new PhoneConnectionTeam(phoneSupport);
const internetSupport = new InternetSupportTeam(phoneConnection);
const internetConnection = new InternetConnectionTeam(internetSupport);


console.log("Problem 1 - internet connection");
internetConnection.handleRequest("internet", "newConnection");

console.log("Problem 2 - phone connection");
internetConnection.handleRequest("phone", "problem");

console.log("Problem 3 - phone support");
internetConnection.handleRequest("phone", "problem");


console.log("Problem 4 - Invalid support");
internetConnection.handleRequest("Laptop", "problem");
