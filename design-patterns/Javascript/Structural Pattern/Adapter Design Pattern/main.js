const USB_A_Connector = require("./usbA_connector");
const Adapter = require("./adapter");

// Creating instances for imported classes

const usbAConnector = new USB_A_Connector();
const adapter = new Adapter(usbAConnector);
console.log(adapter.plugIn());
