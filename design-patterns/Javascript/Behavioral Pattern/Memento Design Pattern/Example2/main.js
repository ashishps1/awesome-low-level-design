const DrawingCanvas = require('./canvas');
const CanvasMemento = require('./memento');
const History = require('./careTaker');

// Create a new drawing canvas (Originator)
const canvas = new DrawingCanvas();

// Create a new History (Caretaker)
const history = new History();

// Draw some shapes on the canvas
canvas.addShape("Circle");
canvas.addShape("Square");

// Show current state of canvas
console.log("Initial Drawing:");
canvas.show(); // Output: Circle, Square

// Save the current state of the canvas
history.saveMemento(canvas.save()); // Save: Circle, Square

// Draw more shapes
canvas.addShape("Triangle");
canvas.addShape("Hexagon");

// Show current state of canvas
console.log("\nAfter Drawing More Shapes:");
canvas.show(); // Output: Circle, Square, Triangle, Hexagon

// Save the current state again
history.saveMemento(canvas.save()); // Save: Circle, Square, Triangle, Hexagon

// Draw another shape
canvas.addShape("Pentagon");

// Show current state of canvas
console.log("\nAfter Adding Pentagon:");
canvas.show(); // Output: Circle, Square, Triangle, Hexagon, Pentagon

// Undo the last action by restoring the previous memento
canvas.restore(history.getLatestMemento());
history.removeLastMemento(); // Remove the latest snapshot

console.log("\nAfter Undo (Restoring Previous State):");
canvas.show(); // Output: Circle, Square, Triangle, Hexagon

// Undo another action
canvas.restore(history.getLatestMemento());
history.removeLastMemento(); // Remove the latest snapshot

console.log("\nAfter Another Undo:");
canvas.show(); // Output: Circle, Square
