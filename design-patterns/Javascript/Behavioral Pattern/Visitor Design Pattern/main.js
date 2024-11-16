const { Circle, Rectangle } = require("./element");
const { AreaVisitor, PerimeterVisitor } = require("./visitor");


const shapes = [
  new Circle(5),
  new Rectangle(10, 20),
];

// Create visitors
const areaVisitor = new AreaVisitor();
const perimeterVisitor = new PerimeterVisitor();

// Calculate areas
console.log("Calculating Areas:");
shapes.forEach((shape) => {
  shape.accept(areaVisitor);
});

// Calculate perimeters
console.log("\nCalculating Perimeters:");
shapes.forEach((shape) => {
  shape.accept(perimeterVisitor);
});
