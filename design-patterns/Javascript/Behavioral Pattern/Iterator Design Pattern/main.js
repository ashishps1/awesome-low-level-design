const ConcreteAggregate = require("./aggregate");
const Book = require("./book");

const library = new ConcreteAggregate();

// Adding books to the library
library.addBook(new Book("To Kill a Mockingbird", "Harper Lee"));
library.addBook(new Book("1984", "George Orwell"));
library.addBook(new Book("The Great Gatsby", "F. Scott Fitzgerald"));
library.addBook(new Book("Moby Dick", "Herman Melville"));

// Creating an iterator for the library
const iterator = library.createIterator();

// Iterating through the collection of books
while (iterator.hasNext()) {
  const book = iterator.next();
  console.log(book.getDetails());
}
