const { WebUI, MobileUI } = require("./observer");
const WeatherStation = require("./publisher");

// Create a WeatherStation instance
const weatherStation = new WeatherStation();

// Create observers
const webUI = new WebUI();
const mobileUI = new MobileUI();

// Register observers with the weather station
weatherStation.addObserver(webUI);
weatherStation.addObserver(mobileUI);

// Change the temperature
weatherStation.setTemperature(25); // Notify the data all observers  
weatherStation.setTemperature(30); // Notify the updated data all observers


// Adding another observer
const webUI2 = new WebUI();
weatherStation.addObserver(webUI2);
weatherStation.setTemperature(35);


// Removing an observer
weatherStation.removeObserver(webUI);
weatherStation.setTemperature(40);
