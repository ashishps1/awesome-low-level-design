// Class for projector functionality

class Projector {
  on() {
    console.log("Projector on");
  }

  connect(source) {
    console.log(`Connecting projector to ${source}`);
  }

  off() {
    console.log("Projector off");
  }
}

module.exports = Projector;
