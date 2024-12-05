// Abstract class for phoneState
class PhoneState {
  alert() {}
  answer() {}
  hangup() {}
}

// Concerte Class for phoneState

// State-1 : Phone is in Ringing State
class Ringing extends PhoneState {
  alert() {
    console.log("Phone is ringing...");
  }
  answer(context) {
    console.log("Phone is answering...");
    context.setState(new InCall());
  }
  hangup() {
    console.log("Cannot hangup while ringing");
  }
}

// State-2 : Phone is in InCall State
class InCall extends PhoneState {
  alert() {
    console.log("Phone is in call...");
  }
  answer() {
    console.log("Cannot answer while in call");
  }
  hangup(context) {
    console.log("Phone is hanging up...");
    context.setState(new Idle());
  }
}

// State-3 : Phone is in Idle State
class Idle extends PhoneState {
  alert() {
    console.log("Phone is idle...");
  }
  answer() {
    console.log("Phone is answering...");
    this.hangup();
  }
  hangup() {
    console.log("Cannot hangup while idle");
  }
}

module.exports = { Ringing, InCall, Idle };
