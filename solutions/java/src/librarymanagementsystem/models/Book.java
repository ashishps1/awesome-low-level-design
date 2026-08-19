package librarymanagementsystem.models;

import java.time.LocalDate;
import java.util.Objects;

/**
 * Represents a Book in the library system.
 * Follows SRP - Only handles book-related data
 * Demonstrates Encapsulation - All fields are private
 */
public class Book {
    private final String isbn;  // Immutable identifier
    private String title;
    private String author;
    private int publicationYear;
    private BookStatus status;
    private String currentBranchId;
    
    public enum BookStatus {
        AVAILABLE,
        CHECKED_OUT,
        RESERVED,
        MAINTENANCE,
        LOST
    }
    
    // Constructor
    public Book(String isbn, String title, String author, int publicationYear) {
        if (isbn == null || isbn.trim().isEmpty()) {
            throw new IllegalArgumentException("ISBN cannot be null or empty");
        }
        this.isbn = isbn;
        this.title = title;
        this.author = author;
        this.publicationYear = publicationYear;
        this.status = BookStatus.AVAILABLE;
    }
    
    // Getters
    public String getIsbn() { return isbn; }
    public String getTitle() { return title; }
    public String getAuthor() { return author; }
    public int getPublicationYear() { return publicationYear; }
    public BookStatus getStatus() { return status; }
    public String getCurrentBranchId() { return currentBranchId; }
    
    // Setters with validation
    public void setTitle(String title) {
        if (title == null || title.trim().isEmpty()) {
            throw new IllegalArgumentException("Title cannot be null or empty");
        }
        this.title = title;
    }
    
    public void setAuthor(String author) {
        if (author == null || author.trim().isEmpty()) {
            throw new IllegalArgumentException("Author cannot be null or empty");
        }
        this.author = author;
    }
    
    public void setStatus(BookStatus status) {
        this.status = status;
    }
    
    public void setCurrentBranchId(String branchId) {
        this.currentBranchId = branchId;
    }
    
    // Business logic methods
    public boolean isAvailable() {
        return status == BookStatus.AVAILABLE;
    }
    
    public void markAsCheckedOut() {
        if (status != BookStatus.AVAILABLE) {
            throw new IllegalStateException("Book is not available for checkout");
        }
        this.status = BookStatus.CHECKED_OUT;
    }
    
    public void markAsReturned() {
        this.status = BookStatus.AVAILABLE;
    }
    
    public void markAsReserved() {
        if (status == BookStatus.AVAILABLE) {
            this.status = BookStatus.RESERVED;
        }
    }
    
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Book book = (Book) o;
        return isbn.equals(book.isbn);
    }
    
    @Override
    public int hashCode() {
        return Objects.hash(isbn);
    }
    
    @Override
    public String toString() {
        return String.format("Book{isbn='%s', title='%s', author='%s', year=%d, status=%s}",
                isbn, title, author, publicationYear, status);
    }
}