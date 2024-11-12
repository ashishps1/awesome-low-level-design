// Abstract product
class Chair {
  sitOn() {
    throw new error("Sitting on chair");
  }
}

class Sofa {
  lieOn() {
    throw new error("Lying on sofa");
  }
}

// Concrete product for modernStyle
class ModernChair extends Chair {
  sitOn() {
    console.log("Sitting on modern chair");
  }
}

class ModernSofa extends Sofa {
  lieOn() {
    console.log("Lying on modern sofa");
  }
}

// Concrete product for classicStyle
class ClassicChair extends Chair {
  sitOn() {
    console.log("Sitting on classic chair");
  }
}

class ClassicSofa extends Sofa {
  lieOn() {
    console.log("Lying on classic sofa");
  }
}

// Abstract factory
class FurnitureFactory {
  createChair() {
    throw new error("Creating chair");
  }
  createSofa() {
    throw new error("Creating sofa");
  }
}

// Concrete factory for modernStyle
class ModernFurnitureFactory extends FurnitureFactory {
  createChair() {
    return new ModernChair();
  }
  createSofa() {
    return new ModernSofa();
  }
}

// Concrete factory for classicStyle
class ClassicFurnitureFactory extends FurnitureFactory {
  createChair() {
    return new ClassicChair();
  }
  createSofa() {
    return new ClassicSofa();
  }
}

module.exports = {
  ModernFurnitureFactory,
  ClassicFurnitureFactory,
};
