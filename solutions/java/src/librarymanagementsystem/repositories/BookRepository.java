package librarymanagementsystem.repositories;

import librarymanagementsystem.models.Book;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Repository for Book entities.
 * Implements Repository pattern and DIP
 * Follows SRP - Only handles book data access
 */
public class BookRepository implements Repository<Book, String> {
    private final Map<String, Book> books;
    
    public BookRepository() {
        this.books = new HashMap<>();
    }
    
    @Override
    public void save(Book book) {
        if (book == null) {
            throw new IllegalArgumentException("Book cannot be null");
        }
        books.put(book.getIsbn(), book);
    }
    
    @Override
    public Optional<Book> findById(String isbn) {
        return Optional.ofNullable(books.get(isbn));
    }
    
    @Override
    public List<Book> findAll() {
        return new ArrayList<>(books.values());
    }
    
    @Override
    public void delete(String isbn) {
        books.remove(isbn);
    }
    
    @Override
    public boolean exists(String isbn) {
        return books.containsKey(isbn);
    }
    
    // Custom query methods
    public List<Book> findByTitle(String title) {
        return books.values().stream()
                .filter(book -> book.getTitle().toLowerCase().contains(title.toLowerCase()))
                .collect(Collectors.toList());
    }
    
    public List<Book> findByAuthor(String author) {
        return books.values().stream()
                .filter(book -> book.getAuthor().toLowerCase().contains(author.toLowerCase()))
                .collect(Collectors.toList());
    }
    
    public List<Book> findAvailableBooks() {
        return books.values().stream()
                .filter(Book::isAvailable)
                .collect(Collectors.toList());
    }
    
    public List<Book> findByBranch(String branchId) {
        return books.values().stream()
                .filter(book -> branchId.equals(book.getCurrentBranchId()))
                .collect(Collectors.toList());
    }
}