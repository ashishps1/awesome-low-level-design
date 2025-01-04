// Abstract Class  or Component class

class Component {
  showDetails() {
    throw new error("This method is overriden by subclasses");
  }
}

module.exports = Component;
