const proxyImage = require("./proxyImage");

const image = new proxyImage("test.jpg");

console.log('First call to display:');
image.display();

console.log('Second call to display:');
image.display();