// careTaker.js

class CareTaker {
  constructor() {
    this.mementos = [];
  }

  saveMemento(memento) {
    this.mementos.push(memento);
  }

  getMemento(index) {
    return this.mementos[index];
  }
}

module.exports = CareTaker;
