// RemoteControl.js

class RemoteControl {
    constructor(device) {
      this.device = device; // This is the bridge to the device
    }
  
    pressOn() {
      this.device.turnOn(); // Call the device's turnOn method
    }
  
    pressOff() {
      this.device.turnOff(); // Call the device's turnOff method
    }
  }
  
  module.exports = RemoteControl;
  