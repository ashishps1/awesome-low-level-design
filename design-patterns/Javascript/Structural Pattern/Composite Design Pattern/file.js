const Component = require("./component");

class File extends Component {
  constructor(name) {
    super();
    this.name = name;
  }

  showDetails() {
    console.log(`File: ${this.name}`);
  }
}

module.exports = File;