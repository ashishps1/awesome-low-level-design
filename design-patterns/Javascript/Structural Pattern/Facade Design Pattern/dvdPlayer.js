// Class for DVD player functionality

class DVDPlayer {
  on() {
    console.log("DVD player is on");
  }
  play(movie) {
    console.log(`Playing ${movie}`);
  }

  off() {
    console.log("DVD player is off");
  }
}

module.exports = DVDPlayer;
