package librarymanagementsystem

import "sync"

type Book struct {
	ISBN            string
	Title           string
	Author          string
	PublicationYear int
	available       bool
	mu              sync.RWMutex
}

func NewBook(isbn, title, author string, publicationYear int) *Book {
	return &Book{
		ISBN:            isbn,
		Title:           title,
		Author:          author,
		PublicationYear: publicationYear,
		available:       true,
	}
}

func (b *Book) IsAvailable() bool {
	b.mu.RLock()
	defer b.mu.RUnlock()
	return b.available
}

func (b *Book) SetAvailable(available bool) {
	b.mu.Lock()
	defer b.mu.Unlock()
	b.available = available
}
