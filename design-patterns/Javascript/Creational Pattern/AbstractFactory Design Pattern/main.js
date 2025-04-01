const {
  ModernFurnitureFactory,
  ClassicFurnitureFactory,
} = require("./abstract");

function createFurniture(factory) {
  const chair = factory.createChair();
  const sofa = factory.createSofa();

  chair.sitOn();
  sofa.lieOn();
}

// Use the Modern Furniture Factory
const modernFactory = new ModernFurnitureFactory();
createFurniture(modernFactory);

// Use the Victorian Furniture Factory
const classicFactory = new ClassicFurnitureFactory();
createFurniture(classicFactory);
