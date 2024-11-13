const CircleFactory = require("./circleFactory");

const circleFactory = new CircleFactory();

const redCircle = circleFactory.getCircle("red");
redCircle.draw("big", 20, 30);

const blueCircle = circleFactory.getCircle("blue");
blueCircle.draw("medium", 200, 300);

const greenCircle = circleFactory.getCircle("red");
greenCircle.draw("medium", 200, 300); // Here it won't create a new object as it already exists.

console.log(
  `Total unique circle instance created are:  ${
    Object.keys(circleFactory.circles).length
  }`
);
