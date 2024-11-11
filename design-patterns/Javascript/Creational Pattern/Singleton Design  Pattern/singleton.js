//Variable to hold the instance
let instance = null;

class Singleton {
  constructor() {
    if (instance) {
      //check if instance already exists
      return instance; //return existing instance
    }
    this.data = 0;
    instance = this;
  }

  // Method to modify data
  increment() {
    this.data += 1;
  }

  // Method to get the current data
  getData() {
    return this.data;
  }
}

module.exports = new Singleton();
