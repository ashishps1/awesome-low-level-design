class WeatherStation {
  constructor() {
    this.observers = [];
    this.temperature = 0;
  }

  //Method to add Subscribers to the list
  addObserver(observer) {
    this.observers.push(observer);
  }

  // Remove Subscribers from the list
  removeObserver(observer) {
    this.observers = this.observers.filter((obs) => obs !== observer);
  }

  // Notify all subscribers
  notifyObservers() {
    this.observers.forEach((observer) => observer.update(this.temperature));
  }

  //Method to set the temperature
  setTemperature(temperature) {
    this.temperature = temperature;
    this.notifyObservers();
  }
}

module.exports = WeatherStation;