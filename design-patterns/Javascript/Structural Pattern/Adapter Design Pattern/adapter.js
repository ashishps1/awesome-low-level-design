// usbAdapter.js

// No need to import USB_A_Connector here

class USB_Adapter {
  constructor(connector) {
    this.connector = connector; // Store the USB-A connector instance
  }

  plugIn() {
    return this.connector.connect(); // Use the method of the passed instances
  }
}

module.exports = USB_Adapter;
