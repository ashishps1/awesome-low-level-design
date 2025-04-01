// Device.js

// The Device interface
class Device {
  turnOn() {
    throw new Error("Method 'turnOn()' must be implemented.");
  }
  turnOff() {
    throw new Error("Method 'turnOff()' must be implemented.");
  }
}

// Concrete class for TV
class TV extends Device {
  turnOn() {
    console.log("TV is now ON.");
  }

  turnOff() {
    console.log("TV is now OFF.");
  }
}

// Concrete class for Radio
class Radio extends Device {
  turnOn() {
    console.log("Radio is now ON.");
  }

  turnOff() {
    console.log("Radio is now OFF.");
  }
}

// Exporting the device classes
module.exports = {
  TV,
  Radio,
};
    