// Proxy object

const realImage = require("./real_Image");

class ProxyImage {
  constructor(fileName) {
    this.fileName = fileName;
    this.realImage = null; // LAZY LOADING (Image not loaded yet)
  }

  display() {
    // Loading the image only if requested
    if (!this.realImage) {
      this.realImage = new realImage(this.fileName);
    }

    this.realImage.display();
  }
}

module.exports = ProxyImage;
