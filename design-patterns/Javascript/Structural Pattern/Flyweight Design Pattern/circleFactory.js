// circleFactory.js

const Circle = require("./circle");

class CircleFactory {
  constructor() {
    this.circles = {}; // Store the created circles
  }

  getCircle(color) {
    // Check if the circle exists
    if (!this.circles[color]) {
      // Create a new circle if it doesn't exist
      this.circles[color] = new Circle(color);
    }
    return this.circles[color];
  }
}

module.exports = CircleFactory;
