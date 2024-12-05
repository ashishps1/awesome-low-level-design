// Import CanvasMemento from memento.js
const CanvasMemento = require("./memento"); // <-- Add this line

class DrawingCanvas {
  constructor() {
    this.shapes = []; // The current shapes drawn on the canvas
  }

  // Method to draw a new shape
  addShape(shape) {
    this.shapes.push(shape);
  }

  // Method to remove the last added shape (simulating undo)
  removeLastShape() {
    this.shapes.pop();
  }

  // Create a memento (save the current state)
  save() {
    return new CanvasMemento([...this.shapes]); // Copy the current shapes to a new Memento
  }

  // Restore the canvas state from a memento
  restore(memento) {
    this.shapes = memento.getState(); // Replace current shapes with the saved shapes
  }

  // Print all shapes (to simulate displaying them on the canvas)
  show() {
    console.log("Current shapes on canvas:", this.shapes);
  }
}

module.exports = DrawingCanvas;
