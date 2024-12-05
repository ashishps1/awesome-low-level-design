const SoundSystem = require("./soundSystem");
const DVDPlayer = require("./dvdPlayer");
const Projector = require("./projector");
const Lights = require("./lights");
const Snacks = require("./snacks");

class MovieFacade {
  constructor() {
    this.soundSystem = new SoundSystem();
    this.dvdPlayer = new DVDPlayer();
    this.projector = new Projector();
    this.lights = new Lights();
    this.snacks = new Snacks();
  }

  watchMovie(movie) {
    console.log(`Starting to watch a movie ${movie}`);
    this.lights.on();
    this.projector.on();
    this.projector.connect("DVD Player");
    this.dvdPlayer.on();
    this.soundSystem.on();
    this.dvdPlayer.play(movie);
    this.soundSystem.setVolume("High");
  }

  getSnacks(snacks) {
    console.log("1st part of the movie is great! Let's order some snacks");
    this.snacks.noteOrder(snacks);
    this.snacks.prepare();
    this.snacks.serve(snacks);
  }

  endMovie() {
    console.log("End of the movie, shutting down");
    this.lights.off();
    this.projector.off();
    this.dvdPlayer.off();
    this.soundSystem.off();
  }
}

module.exports = MovieFacade;
