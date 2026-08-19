package librarymanagementsystem;

import librarymanagementsystem.models.*;
import librarymanagementsystem.services.*;
import librarymanagementsystem.repositories.*;
import librarymanagementsystem.utils.Logger;

import java.util.List;
import java.util.Map;

/**
 * Main Library Management System.
 * Follows SRP - Delegates to service classes
 * Follows DIP - Depends on abstractions (services)
 * Acts as a Facade Pattern - Provides simple interface to complex subsystems
 */
public class LibraryManagementSystem {
    private final BookService bookService;
    private final PatronService patronService;
    private final LoanService loanService;
    private final ReservationService reservationService;
    private final BranchService branchService;
    private final RecommendationService recommendationService;
    
    /**
     * Constructor with dependency injection (DIP).
     */
    public LibraryManagementSystem(
            BookService bookService,
            PatronService patronService,
            LoanService loanService,
            ReservationService reservationService,
            BranchService branchService,
            RecommendationService recommendationService) {
        this.bookService = bookService;
        this.patronService = patronService;
        this.loanService = loanService;
        this.reservationService = reservationService;
        this.branchService = branchService;
        this.recommendationService = recommendationService;
        
        Logger.info("Library Management System initialized");
    }
    
    // ========== Book Management ==========
    
    public void addBook(Book book, String branchId) {
        try {
            bookService.addBook(book, branchId);
            Logger.info("Book added: " + book.getTitle());
        } catch (Exception e) {
            Logger.error("Failed to add book", e);
            throw e;
        }
    }
    
    public void updateBook(Book book) {
        try {
            bookService.updateBook(book);
            Logger.info("Book updated: " + book.getTitle());
        } catch (Exception e) {
            Logger.error("Failed to update book", e);
            throw e;
        }
    }
    
    public void removeBook(String isbn) {
        try {
            bookService.removeBook(isbn);
            Logger.info("Book removed: " + isbn);
        } catch (Exception e) {
            Logger.error("Failed to remove book", e);
            throw e;
        }
    }
    
    public Book getBook(String isbn) {
        return bookService.getBook(isbn);
    }
    
    public List<Book> searchBooks(String query) {
        return bookService.searchBooks(query);
    }
    
    public List<Book> getAllBooks() {
        return bookService.getAllBooks();
    }
    
    public List<Book> getAvailableBooks() {
        return bookService.getAvailableBooks();
    }
    
    // ========== Patron Management ==========
    
    public void registerPatron(Patron patron) {
        try {
            patronService.registerPatron(patron);
            Logger.info("Patron registered: " + patron.getName());
        } catch (Exception e) {
            Logger.error("Failed to register patron", e);
            throw e;
        }
    }
    
    public void updatePatron(Patron patron) {
        try {
            patronService.updatePatron(patron);
            Logger.info("Patron updated: " + patron.getName());
        } catch (Exception e) {
            Logger.error("Failed to update patron", e);
            throw e;
        }
    }
    
    public void removePatron(String patronId) {
        try {
            patronService.removePatron(patronId);
            Logger.info("Patron removed: " + patronId);
        } catch (Exception e) {
            Logger.error("Failed to remove patron", e);
            throw e;
        }
    }
    
    public Patron getPatron(String patronId) {
        return patronService.getPatron(patronId);
    }
    
    public List<Patron> getAllPatrons() {
        return patronService.getAllPatrons();
    }
    
    public List<Patron> searchPatronsByName(String name) {
        return patronService.searchPatronsByName(name);
    }
    
    // ========== Lending Operations ==========
    
    public LoanRecord checkoutBook(String isbn, String patronId) {
        try {
            LoanRecord loan = loanService.checkoutBook(isbn, patronId);
            Logger.info("Book checked out: " + isbn + " to patron: " + patronId);
            return loan;
        } catch (Exception e) {
            Logger.error("Failed to checkout book", e);
            throw e;
        }
    }
    
    public void returnBook(String isbn, String patronId) {
        try {
            loanService.returnBook(isbn, patronId);
            
            // Process reservations when book is returned
            reservationService.processBookReturn(isbn);
            
            Logger.info("Book returned: " + isbn + " by patron: " + patronId);
        } catch (Exception e) {
            Logger.error("Failed to return book", e);
            throw e;
        }
    }
    
    public List<LoanRecord> getActiveLoans() {
        return loanService.getActiveLoans();
    }
    
    public List<LoanRecord> getOverdueLoans() {
        return loanService.getOverdueLoans();
    }
    
    public List<LoanRecord> getPatronHistory(String patronId) {
        return loanService.getPatronHistory(patronId);
    }
    
    // ========== Reservation System ==========
    
    public Reservation reserveBook(String isbn, String patronId) {
        try {
            Reservation reservation = reservationService.reserveBook(isbn, patronId);
            Logger.info("Book reserved: " + isbn + " for patron: " + patronId);
            return reservation;
        } catch (Exception e) {
            Logger.error("Failed to reserve book", e);
            throw e;
        }
    }
    
    public void cancelReservation(String isbn, String patronId) {
        try {
            reservationService.cancelReservation(isbn, patronId);
            Logger.info("Reservation cancelled: " + isbn + " for patron: " + patronId);
        } catch (Exception e) {
            Logger.error("Failed to cancel reservation", e);
            throw e;
        }
    }
    
    public List<Reservation> getReservationsForBook(String isbn) {
        return reservationService.getReservationsForBook(isbn);
    }
    
    public int getQueuePosition(String isbn, String patronId) {
        return reservationService.getQueuePosition(isbn, patronId);
    }
    
    // ========== Multi-Branch Support ==========
    
    public void addBranch(Branch branch) {
        try {
            branchService.addBranch(branch);
            Logger.info("Branch added: " + branch.getBranchName());
        } catch (Exception e) {
            Logger.error("Failed to add branch", e);
            throw e;
        }
    }
    
    public Branch getBranch(String branchId) {
        return branchService.getBranch(branchId);
    }
    
    public List<Branch> getAllBranches() {
        return branchService.getAllBranches();
    }
    
    public void transferBook(String isbn, String fromBranchId, String toBranchId) {
        try {
            branchService.transferBook(isbn, fromBranchId, toBranchId);
            Logger.info("Book transferred: " + isbn + " from " + fromBranchId + " to " + toBranchId);
        } catch (Exception e) {
            Logger.error("Failed to transfer book", e);
            throw e;
        }
    }
    
    public List<Book> getBranchInventory(String branchId) {
        return branchService.getBranchInventory(branchId);
    }
    
    public Map<String, List<Book>> searchBookAcrossBranches(String query) {
        return branchService.searchBookAcrossBranches(query);
    }
    
    // ========== Recommendation System ==========
    
    public List<Book> getRecommendations(String patronId, int limit) {
        try {
            Patron patron = patronService.getPatron(patronId);
            return recommendationService.recommendBooks(patron, limit);
        } catch (Exception e) {
            Logger.error("Failed to get recommendations", e);
            throw e;
        }
    }
    
    public List<Book> getPopularBooks(int limit) {
        return recommendationService.getPopularBooks(limit);
    }
    
    public List<Book> getSimilarBooks(String isbn, int limit) {
        return recommendationService.getSimilarBooks(isbn, limit);
    }
}