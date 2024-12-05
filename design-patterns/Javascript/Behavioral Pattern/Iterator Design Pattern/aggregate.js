const { LibraryIterator } = require("./iterator");
const Book = require("./book");

class Aggregate {
  createIterator() {
    throw new Error("Method 'createIterator()' must be implemented.");
  }
}

class ConcreteAggregate extends Aggregate {
  constructor() {
    super();
    this.books = [];
  }

  addBook(book) {
    this.books.push(book);
  }

  createIterator() {
    return new LibraryIterator(this.books);
  }
}

module.exports = ConcreteAggregate;
