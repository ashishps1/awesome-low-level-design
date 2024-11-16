// element.js
class Shape {
  accept(visitor) {
    throw new Error("This method should be overridden!");
  }
}

class Circle extends Shape {
  constructor(radius) {
    super();
    this.radius = radius;
  }

  accept(visitor) {
    visitor.visitCircle(this);
  }
}
class Rectangle extends Shape {
  constructor(width, height) {
    super();
    this.width = width;
    this.height = height;
  }

  accept(visitor) {
    visitor.visitRectangle(this);
  }
}

module.exports = {Circle,Rectangle};
