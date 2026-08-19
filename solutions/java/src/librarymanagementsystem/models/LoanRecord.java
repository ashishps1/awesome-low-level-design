package librarymanagementsystem.models;

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

/**
 * Represents a loan record for tracking book borrowing.
 * Follows SRP - Only handles loan-related data and calculations
 */
public class LoanRecord {
    private final String loanId;
    private final Book book;
    private final Patron patron;
    private final LocalDate checkoutDate;
    private LocalDate dueDate;
    private LocalDate returnDate;
    private double lateFee;
    private LoanStatus status;
    
    public enum LoanStatus {
        ACTIVE,
        RETURNED,
        OVERDUE
    }
    
    // Constructor
    public LoanRecord(String loanId, Book book, Patron patron, LocalDate checkoutDate, int loanPeriodDays) {
        this.loanId = loanId;
        this.book = book;
        this.patron = patron;
        this.checkoutDate = checkoutDate;
        this.dueDate = checkoutDate.plusDays(loanPeriodDays);
        this.status = LoanStatus.ACTIVE;
        this.lateFee = 0.0;
    }
    
    // Getters
    public String getLoanId() { return loanId; }
    public Book getBook() { return book; }
    public Patron getPatron() { return patron; }
    public LocalDate getCheckoutDate() { return checkoutDate; }
    public LocalDate getDueDate() { return dueDate; }
    public LocalDate getReturnDate() { return returnDate; }
    public double getLateFee() { return lateFee; }
    public LoanStatus getStatus() { return status; }
    
    // Business logic methods
    public void returnBook(LocalDate returnDate) {
        this.returnDate = returnDate;
        this.status = LoanStatus.RETURNED;
        
        if (returnDate.isAfter(dueDate)) {
            calculateLateFee(returnDate);
        }
    }
    
    public void calculateLateFee(LocalDate returnDate) {
        long daysLate = ChronoUnit.DAYS.between(dueDate, returnDate);
        if (daysLate > 0) {
            this.lateFee = daysLate * 0.50; // $0.50 per day
            this.status = LoanStatus.OVERDUE;
        }
    }
    
    public boolean isOverdue() {
        return LocalDate.now().isAfter(dueDate) && status == LoanStatus.ACTIVE;
    }
    
    public long getDaysUntilDue() {
        return ChronoUnit.DAYS.between(LocalDate.now(), dueDate);
    }
    
    @Override
    public String toString() {
        return String.format("LoanRecord{id='%s', book='%s', patron='%s', due=%s, status=%s}",
                loanId, book.getTitle(), patron.getName(), dueDate, status);
    }
}