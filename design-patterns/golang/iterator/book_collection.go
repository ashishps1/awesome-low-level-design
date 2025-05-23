package iterator

// BookCollection represents a collection of books
type BookCollection struct {
	books []*Book
}

// NewBookCollection creates a new BookCollection instance
func NewBookCollection() *BookCollection {
	return &BookCollection{
		books: make([]*Book, 0),
	}
}

// AddBook adds a book to the collection
func (bc *BookCollection) AddBook(book *Book) {
	bc.books = append(bc.books, book)
}

// CreateIterator creates a new iterator for the book collection
func (bc *BookCollection) CreateIterator() Iterator {
	return NewBookIterator(bc)
}

// BookIterator represents an iterator for the book collection
type BookIterator struct {
	collection *BookCollection
	index      int
}

// NewBookIterator creates a new BookIterator instance
func NewBookIterator(collection *BookCollection) *BookIterator {
	return &BookIterator{
		collection: collection,
		index:      0,
	}
}

// HasNext checks if there are more books to iterate
func (bi *BookIterator) HasNext() bool {
	return bi.index < len(bi.collection.books)
}

// Next returns the next book in the collection
func (bi *BookIterator) Next() interface{} {
	if bi.HasNext() {
		book := bi.collection.books[bi.index]
		bi.index++
		return book
	}
	return nil
}
