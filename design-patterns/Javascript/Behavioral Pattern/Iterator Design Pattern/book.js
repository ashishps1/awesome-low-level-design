class Book {
  constructor(title, author) {
    this.title = title;
    this.author = author;
  }

  getDetails() {
    return `${this.title} by ${this.author}`;
  }
}

module.exports = Book;
