// CareTaker -> Manages mementos

class History {
  constructor() {
    this.mementos = []; // List of saved mementos
  }

  // Save a memento
  saveMemento(memento) {
    this.mementos.push(memento);
  }

  // Get a memento
  getMemento(index) {
    return this.mementos[index];
  }

  // Remove the last memento
  removeMemento() {
    return this.mementos.pop();
  }
  getLatestMemento() {
    return this.mementos.length > 0
      ? this.mementos[this.mementos.length - 1]
      : null;
  }

  removeLastMemento() {
    if (this.mementos.length > 0) {
      this.mementos.pop();
    }
  }
}

module.exports = History;
