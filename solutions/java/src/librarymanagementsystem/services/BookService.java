package librarymanagementsystem.services;

import librarymanagementsystem.models.Book;
import librarymanagementsystem.repositories.BookRepository;
import librarymanagementsystem.exceptions.BookNotFoundException;
import java.util.List;

/**
 * Service for book management operations.
 * Follows SRP - Only handles book-related business logic
 * Follows DIP - Depends on BookRepository abstraction
 */
public class BookService {
    private final BookRepository bookRepository;
    
    public BookService(BookRepository bookRepository) {
        this.bookRepository = bookRepository;
    }
    
    public void addBook(Book book, String branchId) {
        book.setCurrentBranchId(branchId);
        bookRepository.save(book);
        System.out.println("✅ Book added: " + book.getTitle());
    }
    
    public void updateBook(Book book) {
        if (!bookRepository.exists(book.getIsbn())) {
            throw new BookNotFoundException("Book not found: " + book.getIsbn());
        }
        bookRepository.save(book);
        System.out.println("✅ Book updated: " + book.getTitle());
    }
    
    public void removeBook(String isbn) {
        if (!bookRepository.exists(isbn)) {
            throw new BookNotFoundException("Book not found: " + isbn);
        }
        bookRepository.delete(isbn);
        System.out.println("✅ Book removed: " + isbn);
    }
    
    public Book getBook(String isbn) {
        return bookRepository.findById(isbn)
                .orElseThrow(() -> new BookNotFoundException("Book not found: " + isbn));
    }
    
    public List<Book> searchBooks(String query) {
        List<Book> results = bookRepository.findByTitle(query);
        results.addAll(bookRepository.findByAuthor(query));
        return results;
    }
    
    public List<Book> getAllBooks() {
        return bookRepository.findAll();
    }
    
    public List<Book> getAvailableBooks() {
        return bookRepository.findAvailableBooks();
    }
}