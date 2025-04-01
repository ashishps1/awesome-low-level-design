package librarymanagementsystem

import "sync"

type Member struct {
	MemberID      string
	Name          string
	ContactInfo   string
	borrowedBooks map[string]*Book // Using map for O(1) lookups
	mu            sync.RWMutex
}

func NewMember(memberID, name, contactInfo string) *Member {
	return &Member{
		MemberID:      memberID,
		Name:          name,
		ContactInfo:   contactInfo,
		borrowedBooks: make(map[string]*Book),
	}
}

func (m *Member) BorrowBook(book *Book) {
	m.mu.Lock()
	defer m.mu.Unlock()
	m.borrowedBooks[book.ISBN] = book
}

func (m *Member) ReturnBook(book *Book) {
	m.mu.Lock()
	defer m.mu.Unlock()
	delete(m.borrowedBooks, book.ISBN)
}

func (m *Member) GetBorrowedBooks() []*Book {
	m.mu.RLock()
	defer m.mu.RUnlock()
	books := make([]*Book, 0, len(m.borrowedBooks))
	for _, book := range m.borrowedBooks {
		books = append(books, book)
	}
	return books
}
