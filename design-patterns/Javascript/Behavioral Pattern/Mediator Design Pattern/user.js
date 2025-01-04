class User {
  constructor(name, mediator) {
    this.name = name;
    this.mediator = mediator;
  }

  send(message) {
    console.log(`${this.name} sent: ${message}`);
    this.mediator.send(message, this);
  }

  receive(message) { 
    console.log(`${this.name} receives message: ${message}`);
  }
}

module.exports = User;