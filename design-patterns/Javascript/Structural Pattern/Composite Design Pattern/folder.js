const Component = require("./component");

// Composite: Folder that can hold files or other folders

class Folder extends Component {
  constructor(name) {
    super();
    this.name = name;
    this.files = [];
  }

  add(file) {
    this.files.push(file);
  }

  showDetails() {
    console.log(`Folder: ${this.name}`);
    this.files.forEach((file) => file.showDetails());
  }
}

module.exports = Folder;
