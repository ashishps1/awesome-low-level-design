package librarymanagementsystem.services;

import librarymanagementsystem.models.Book;
import librarymanagementsystem.models.Patron;
import librarymanagementsystem.models.LoanRecord;
import librarymanagementsystem.repositories.BookRepository;
import librarymanagementsystem.repositories.PatronRepository;
import librarymanagementsystem.repositories.LoanRepository;
import librarymanagementsystem.exceptions.BookNotFoundException;
import librarymanagementsystem.exceptions.PatronNotFoundException;
import librarymanagementsystem.exceptions.BookNotAvailableException;
import librarymanagementsystem.patterns.strategy.LateFeeStrategy;
import librarymanagementsystem.patterns.strategy.BookLateFeeStrategy;

import java.time.LocalDate;
import java.util.List;
import java.util.UUID;

/**
 * Service for loan management operations (checkout/return).
 * Follows SRP - Only handles loan-related business logic
 * Follows DIP - Depends on repository abstractions
 * Uses Strategy Pattern for late fee calculation
 */
public class LoanService {
    private final BookRepository bookRepository;
    private final PatronRepository patronRepository;
    private final LoanRepository loanRepository;
    private final NotificationService notificationService;
    private final LateFeeStrategy lateFeeStrategy;
    
    private static final int DEFAULT_LOAN_PERIOD_DAYS = 14;
    
    public LoanService(
            BookRepository bookRepository,
            PatronRepository patronRepository,
            LoanRepository loanRepository,
            NotificationService notificationService) {
        this.bookRepository = bookRepository;
        this.patronRepository = patronRepository;
        this.loanRepository = loanRepository;
        this.notificationService = notificationService;
        this.lateFeeStrategy = new BookLateFeeStrategy(); // Default strategy
    }
    
    /**
     * Checkout a book to a patron.
     */
    public LoanRecord checkoutBook(String isbn, String patronId) {
        // Retrieve book and patron
        Book book = bookRepository.findById(isbn)
                .orElseThrow(() -> new BookNotFoundException("Book not found: " + isbn));
        
        Patron patron = patronRepository.findById(patronId)
                .orElseThrow(() -> new PatronNotFoundException("Patron not found: " + patronId));
        
        // Validate business rules
        if (!book.isAvailable()) {
            throw new BookNotAvailableException("Book is not available: " + book.getTitle());
        }
        
        if (!patron.canBorrowMoreBooks()) {
            throw new IllegalStateException(
                "Patron has reached borrowing limit: " + patron.getCurrentBorrowedCount() + 
                "/" + patron.getMaxBooksAllowed()
            );
        }
        
        // Create loan record
        String loanId = UUID.randomUUID().toString();
        LoanRecord loan = new LoanRecord(
            loanId, 
            book, 
            patron, 
            LocalDate.now(), 
            DEFAULT_LOAN_PERIOD_DAYS
        );
        
        // Update book status
        book.markAsCheckedOut();
        bookRepository.save(book);
        
        // Update patron
        patron.addBorrowedBook(book);
        patronRepository.save(patron);
        
        // Save loan record
        loanRepository.save(loan);
        
        // Send notification
        notificationService.sendNotification(
            patron.getEmail(),
            "Book checked out: " + book.getTitle() + ". Due date: " + loan.getDueDate()
        );
        
        System.out.println("✅ Book checked out: " + book.getTitle() + " to " + patron.getName());
        return loan;
    }
    
    /**
     * Return a book.
     */
    public void returnBook(String isbn, String patronId) {
        // Find active loan
        List<LoanRecord> patronLoans = loanRepository.findByPatronId(patronId);
        LoanRecord activeLoan = patronLoans.stream()
                .filter(loan -> loan.getBook().getIsbn().equals(isbn))
                .filter(loan -> loan.getStatus() == LoanRecord.LoanStatus.ACTIVE)
                .findFirst()
                .orElseThrow(() -> new IllegalStateException("No active loan found for this book and patron"));
        
        Book book = activeLoan.getBook();
        Patron patron = activeLoan.getPatron();
        
        // Process return
        LocalDate returnDate = LocalDate.now();
        activeLoan.returnBook(returnDate);
        
        // Update book status
        book.markAsReturned();
        bookRepository.save(book);
        
        // Update patron
        patron.removeBorrowedBook(book);
        patron.addToHistory(activeLoan);
        patronRepository.save(patron);
        
        // Save loan record
        loanRepository.save(activeLoan);
        
        // Handle late fees
        if (activeLoan.getLateFee() > 0) {
            notificationService.sendNotification(
                patron.getEmail(),
                "Book returned late. Late fee: $" + String.format("%.2f", activeLoan.getLateFee())
            );
            System.out.println("⚠️ Late fee charged: $" + String.format("%.2f", activeLoan.getLateFee()));
        } else {
            notificationService.sendNotification(
                patron.getEmail(),
                "Book returned: " + book.getTitle() + ". Thank you!"
            );
        }
        
        System.out.println("✅ Book returned: " + book.getTitle() + " by " + patron.getName());
    }
    
    /**
     * Get all active loans.
     */
    public List<LoanRecord> getActiveLoans() {
        return loanRepository.findActiveLoans();
    }
    
    /**
     * Get all overdue loans.
     */
    public List<LoanRecord> getOverdueLoans() {
        return loanRepository.findOverdueLoans();
    }
    
    /**
     * Get patron's borrowing history.
     */
    public List<LoanRecord> getPatronHistory(String patronId) {
        return loanRepository.findByPatronId(patronId);
    }
    
    /**
     * Get book's loan history.
     */
    public List<LoanRecord> getBookHistory(String isbn) {
        return loanRepository.findByIsbn(isbn);
    }
}