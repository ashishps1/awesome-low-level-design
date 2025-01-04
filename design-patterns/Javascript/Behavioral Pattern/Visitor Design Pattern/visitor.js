// Visitor Interface
class ShapeVisitor {
  visitCircle(circle) {
    throw new Error(`This circle method should be overridden!`);
  }

  visitRectangle(rectangle) {
    throw new Error(`This rectangke method should be overridden!`);
  }
}

// Concrete visitor classes
class AreaVisitor extends ShapeVisitor {
  visitCircle(circle) {
    const area = Math.PI * circle.radius * circle.radius;
    console.log(`Aread of circle: ${area}`);
  }

  visitRectangle(rectangle) {
    const area = rectangle.width * rectangle.height;
    console.log(`Area of rectangle: ${area}`);
  }
}

class PerimeterVisitor extends ShapeVisitor {
  visitCircle(circle) {
    const perimeter = 2 * Math.PI * circle.radius;
    console.log(`Perimeter of circle: ${perimeter}`);
  }

  visitRectangle(rectangle) {
    const perimeter = 2 * (rectangle.width + rectangle.height);
    console.log(`Perimeter of rectangle: ${perimeter}`);
  }
}

module.exports = { AreaVisitor, PerimeterVisitor };
