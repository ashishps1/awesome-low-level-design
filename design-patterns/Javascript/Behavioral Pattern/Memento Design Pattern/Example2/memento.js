// Memento -> Stores the snapshot of canvas state
class CanvasMemento {
  constructor(state) {
    this.state = state; // The saved shapes at this point
  }

  // Returns the saved state
  getState() {
    return this.state;
  }
}

module.exports = CanvasMemento;
