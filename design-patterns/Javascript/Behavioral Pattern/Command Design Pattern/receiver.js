// Receiver for Light
class Light {
  turnOn() {
    console.log("The light is on.");
  }

  turnOff() {
    console.log("The light is off.");
  }
}

// Receiver for Fan
class Fan {
  turnOn() {
    console.log("The fan is on.");
  }

  turnOff() {
    console.log("The fan is off.");
  }
}

module.exports = { Light, Fan };
