package librarymanagementsystem.models;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Objects;

/**
 * Represents a library patron (member).
 * Follows SRP - Only handles patron-related data
 */
public class Patron {
    private final String patronId;
    private String name;
    private String email;
    private String phoneNumber;
    private PatronType patronType;
    private List<LoanRecord> borrowingHistory;
    private List<Book> currentlyBorrowedBooks;
    private int maxBooksAllowed;
    
    public enum PatronType {
        REGULAR(5),
        PREMIUM(10),
        STUDENT(3);
        
        private final int maxBooks;
        
        PatronType(int maxBooks) {
            this.maxBooks = maxBooks;
        }
        
        public int getMaxBooks() {
            return maxBooks;
        }
    }
    
    // Constructor
    public Patron(String patronId, String name, String email, PatronType patronType) {
        if (patronId == null || patronId.trim().isEmpty()) {
            throw new IllegalArgumentException("Patron ID cannot be null or empty");
        }
        this.patronId = patronId;
        this.name = name;
        this.email = email;
        this.patronType = patronType;
        this.maxBooksAllowed = patronType.getMaxBooks();
        this.borrowingHistory = new ArrayList<>();
        this.currentlyBorrowedBooks = new ArrayList<>();
    }
    
    // Getters
    public String getPatronId() { return patronId; }
    public String getName() { return name; }
    public String getEmail() { return email; }
    public String getPhoneNumber() { return phoneNumber; }
    public PatronType getPatronType() { return patronType; }
    public int getMaxBooksAllowed() { return maxBooksAllowed; }
    
    public List<LoanRecord> getBorrowingHistory() {
        return Collections.unmodifiableList(borrowingHistory);
    }
    
    public List<Book> getCurrentlyBorrowedBooks() {
        return Collections.unmodifiableList(currentlyBorrowedBooks);
    }
    
    // Setters
    public void setName(String name) { this.name = name; }
    public void setEmail(String email) { this.email = email; }
    public void setPhoneNumber(String phoneNumber) { this.phoneNumber = phoneNumber; }
    
    public void setPatronType(PatronType patronType) {
        this.patronType = patronType;
        this.maxBooksAllowed = patronType.getMaxBooks();
    }
    
    // Business logic methods
    public boolean canBorrowMoreBooks() {
        return currentlyBorrowedBooks.size() < maxBooksAllowed;
    }
    
    public void addBorrowedBook(Book book) {
        if (!canBorrowMoreBooks()) {
            throw new IllegalStateException("Patron has reached maximum borrowing limit");
        }
        currentlyBorrowedBooks.add(book);
    }
    
    public void removeBorrowedBook(Book book) {
        currentlyBorrowedBooks.remove(book);
    }
    
    public void addToHistory(LoanRecord record) {
        borrowingHistory.add(record);
    }
    
    public int getCurrentBorrowedCount() {
        return currentlyBorrowedBooks.size();
    }
    
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Patron patron = (Patron) o;
        return patronId.equals(patron.patronId);
    }
    
    @Override
    public int hashCode() {
        return Objects.hash(patronId);
    }
    
    @Override
    public String toString() {
        return String.format("Patron{id='%s', name='%s', type=%s, borrowed=%d/%d}",
                patronId, name, patronType, currentlyBorrowedBooks.size(), maxBooksAllowed);
    }
}