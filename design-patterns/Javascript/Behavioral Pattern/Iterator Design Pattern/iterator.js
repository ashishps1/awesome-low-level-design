class Iterator {
  next() {
    throw new Error("Method 'next()' must be implemented.");
  }

  hasNext() {
    throw new Error("Method 'hasNext()' must be implemented.");
  }
}

// Concrete Iterator
class LibraryIterator extends Iterator {
  constructor(collection) {
    super();
    this.collection = collection;
    this.index = 0;
  }

  hasNext() {
    return this.index < this.collection.length;
  }


  next() {
    console.log("Current index: " + this.index);
    return this.collection[this.index++];
  }
}

module.exports = { Iterator, LibraryIterator };
