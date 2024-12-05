class realImage {
  constructor(fileName) {
    this.fileName = fileName;
    this.loadFromDisk();
  }

  loadFromDisk() {
    console.log(`Loading image from disk: ${this.fileName}`);
  }

  display() {
    console.log(`Displaying image: ${this.fileName}`);
  }
}

module.exports = realImage;
