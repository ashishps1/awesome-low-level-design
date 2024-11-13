// client code for facade design pattern

const MovieFacade = require("./movieFacade");

const movieFacade = new MovieFacade();
// By getting the required data, we can proceed all the functionality using facade design pattern.

movieFacade.watchMovie("Goat 🍾🎉");
movieFacade.getSnacks("Popcorn");
movieFacade.endMovie();