package iterator

// Book represents a book with title and author
type Book struct {
	Title  string
	Author string
}

// NewBook creates a new Book instance
func NewBook(title, author string) *Book {
	return &Book{
		Title:  title,
		Author: author,
	}
}
