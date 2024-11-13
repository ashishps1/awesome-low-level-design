// Class for snacks functionality

class Snacks {
  noteOrder(snacks) {
    console.log(`Ordering ${snacks}`);
  }
  prepare() {
    console.log("Preparing snacks 🍿");
  }

  serve(snacks) {
    console.log(`Here is your ${snacks} sir!, enjoy your movie 😊`);
  }
}

module.exports = Snacks;
