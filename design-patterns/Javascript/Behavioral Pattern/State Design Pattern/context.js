const {Idle} = require("./state");

// Context Class
class Phone {
  constructor() {
    this.state = new Idle(); // Inital state
  }
  setState(state) {
    this.state = state;
  }
  alert() {
    this.state.alert();
  }
  answer() {
    this.state.answer(this);
  }
  hangup() {
    this.state.hangup(this);
  }
}

module.exports = Phone;