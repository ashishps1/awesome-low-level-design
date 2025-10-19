package librarymanagementsystem;

import librarymanagementsystem.models.*;
import librarymanagementsystem.services.*;
import librarymanagementsystem.repositories.*;
import librarymanagementsystem.utils.IdGenerator;
import librarymanagementsystem.patterns.factory.LibraryItemFactory;

import java.util.List;
import java.util.Map;

/**
 * Demo class to showcase Library Management System functionality.
 * Demonstrates all features including:
 * - Book Management
 * - Patron Management
 * - Lending Process
 * - Reservation System
 * - Multi-branch Support
 * - Recommendation System
 * - Design Patterns (Observer, Factory, Strategy)
 */
public class LibraryDemo {
    
    public static void main(String[] args) {
        System.out.println("=".repeat(60));
        System.out.println("📚 LIBRARY MANAGEMENT SYSTEM DEMO");
        System.out.println("=".repeat(60));
        System.out.println();
        
        // Initialize system
        LibraryManagementSystem library = initializeSystem();
        
        // Demo scenarios
        demoBookManagement(library);
        demoPatronManagement(library);
        demoLendingProcess(library);
        demoReservationSystem(library);
        demoMultiBranchSupport(library);
        demoRecommendationSystem(library);
        demoDesignPatterns();
        
        System.out.println("\n" + "=".repeat(60));
        System.out.println("✅ DEMO COMPLETED SUCCESSFULLY");
        System.out.println("=".repeat(60));
    }
    
    /**
     * Initialize the library system with dependencies (DIP).
     */
    private static LibraryManagementSystem initializeSystem() {
        System.out.println("🔧 Initializing Library Management System...\n");
        
        // Create repositories
        BookRepository bookRepo = new BookRepository();
        PatronRepository patronRepo = new PatronRepository();
        LoanRepository loanRepo = new LoanRepository();
        
        // Create services
        NotificationService notificationService = new NotificationService();
        BookService bookService = new BookService(bookRepo);
        PatronService patronService = new PatronService(patronRepo);
        LoanService loanService = new LoanService(bookRepo, patronRepo, loanRepo, notificationService);
        ReservationService reservationService = new ReservationService(bookRepo, patronRepo, notificationService);
        BranchService branchService = new BranchService(bookRepo);
        RecommendationService recommendationService = new RecommendationService(bookRepo, loanRepo);
        
        // Create main system
        return new LibraryManagementSystem(
            bookService,
            patronService,
            loanService,
            reservationService,
            branchService,
            recommendationService
        );
    }
    
    /**
     * Demo 1: Book Management (Add, Update, Search, Remove).
     */
    private static void demoBookManagement(LibraryManagementSystem library) {
        System.out.println("\n" + "-".repeat(60));
        System.out.println("📖 DEMO 1: BOOK MANAGEMENT");
        System.out.println("-".repeat(60));
        
        // Create branches first
        Branch mainBranch = new Branch("BR001", "Main Library", "123 Main St");
        library.addBranch(mainBranch);
        
        // Add books
        Book book1 = new Book("978-0132350884", "Clean Code", "Robert C. Martin", 2008);
        Book book2 = new Book("978-0201633610", "Design Patterns", "Gang of Four", 1994);
        Book book3 = new Book("978-0134685991", "Effective Java", "Joshua Bloch", 2017);
        Book book4 = new Book("978-0596007126", "Head First Design Patterns", "Eric Freeman", 2004);
        
        library.addBook(book1, "BR001");
        library.addBook(book2, "BR001");
        library.addBook(book3, "BR001");
        library.addBook(book4, "BR001");
        
        System.out.println("\n📚 Total books in library: " + library.getAllBooks().size());
        
        // Search books
        System.out.println("\n🔍 Searching for 'Design':");
        List<Book> searchResults = library.searchBooks("Design");
        searchResults.forEach(book -> System.out.println("   - " + book.getTitle() + " by " + book.getAuthor()));
        
        // Update book
        book1.setTitle("Clean Code: A Handbook of Agile Software Craftsmanship");
        library.updateBook(book1);
        
        System.out.println("\n✅ Book Management Demo Completed");
    }
    
    /**
     * Demo 2: Patron Management (Register, Update, Search).
     */
    private static void demoPatronManagement(LibraryManagementSystem library) {
        System.out.println("\n" + "-".repeat(60));
        System.out.println("👥 DEMO 2: PATRON MANAGEMENT");
        System.out.println("-".repeat(60));
        
        // Register patrons
        Patron patron1 = new Patron("P001", "Alice Johnson", "alice@email.com", Patron.PatronType.REGULAR);
        Patron patron2 = new Patron("P002", "Bob Smith", "bob@email.com", Patron.PatronType.PREMIUM);
        Patron patron3 = new Patron("P003", "Charlie Brown", "charlie@email.com", Patron.PatronType.STUDENT);
        
        library.registerPatron(patron1);
        library.registerPatron(patron2);
        library.registerPatron(patron3);
        
        System.out.println("\n👥 Total patrons: " + library.getAllPatrons().size());
        
        // Display patron info
        System.out.println("\n📋 Patron Details:");
        library.getAllPatrons().forEach(patron -> 
            System.out.println("   - " + patron.getName() + " (" + patron.getPatronType() + 
                             ") - Max books: " + patron.getMaxBooksAllowed())
        );
        
        // Update patron
        patron1.setPatronType(Patron.PatronType.PREMIUM);
        library.updatePatron(patron1);
        System.out.println("\n✅ " + patron1.getName() + " upgraded to PREMIUM");
        
        System.out.println("\n✅ Patron Management Demo Completed");
    }
    
    /**
     * Demo 3: Lending Process (Checkout, Return, Late Fees).
     */
    private static void demoLendingProcess(LibraryManagementSystem library) {
        System.out.println("\n" + "-".repeat(60));
        System.out.println("📤 DEMO 3: LENDING PROCESS");
        System.out.println("-".repeat(60));
        
        // Checkout books
        System.out.println("\n📤 Checking out books...");
        LoanRecord loan1 = library.checkoutBook("978-0132350884", "P001");
        LoanRecord loan2 = library.checkoutBook("978-0201633610", "P002");
        LoanRecord loan3 = library.checkoutBook("978-0134685991", "P001");
        
        System.out.println("\n📊 Active Loans: " + library.getActiveLoans().size());
        
        // Display loan details
        System.out.println("\n📋 Loan Details:");
        library.getActiveLoans().forEach(loan -> 
            System.out.println("   - " + loan.getBook().getTitle() + 
                             " borrowed by " + loan.getPatron().getName() + 
                             " (Due: " + loan.getDueDate() + ")")
        );
        
        // Return a book
        System.out.println("\n📥 Returning book...");
        library.returnBook("978-0132350884", "P001");
        
        System.out.println("\n📊 Active Loans after return: " + library.getActiveLoans().size());
        
        // Check patron history
        System.out.println("\n📜 Patron P001 Borrowing History:");
        List<LoanRecord> history = library.getPatronHistory("P001");
        history.forEach(loan -> 
            System.out.println("   - " + loan.getBook().getTitle() + 
                             " (Status: " + loan.getStatus() + ")")
        );
        
        System.out.println("\n✅ Lending Process Demo Completed");
    }
    
    /**
     * Demo 4: Reservation System (Reserve, Notify, Cancel).
     */
    private static void demoReservationSystem(LibraryManagementSystem library) {
        System.out.println("\n" + "-".repeat(60));
        System.out.println("🔖 DEMO 4: RESERVATION SYSTEM");
        System.out.println("-".repeat(60));
        
        // Try to reserve a checked-out book
        System.out.println("\n🔖 Reserving checked-out book...");
        try {
            Reservation reservation1 = library.reserveBook("978-0201633610", "P003");
            System.out.println("✅ Reservation created: " + reservation1.getReservationId());
            
            // Check queue position
            int position = library.getQueuePosition("978-0201633610", "P003");
            System.out.println("📍 Queue position: " + position);
            
            // Another patron reserves the same book
            Reservation reservation2 = library.reserveBook("978-0201633610", "P001");
            int position2 = library.getQueuePosition("978-0201633610", "P001");
            System.out.println("📍 Second patron queue position: " + position2);
            
        } catch (Exception e) {
            System.out.println("❌ Reservation failed: " + e.getMessage());
        }
        
        // Return the book and trigger notification
        System.out.println("\n📥 Returning reserved book (triggers notification)...");
        library.returnBook("978-0201633610", "P002");
        
        System.out.println("\n✅ Reservation System Demo Completed");
    }
    
    /**
     * Demo 5: Multi-Branch Support (Add Branch, Transfer Books).
     */
    private static void demoMultiBranchSupport(LibraryManagementSystem library) {
        System.out.println("\n" + "-".repeat(60));
        System.out.println("🏢 DEMO 5: MULTI-BRANCH SUPPORT");
        System.out.println("-".repeat(60));
        
        // Add new branch
        Branch branch2 = new Branch("BR002", "Downtown Library", "456 Downtown Ave");
        library.addBranch(branch2);
        
        System.out.println("\n🏢 Total branches: " + library.getAllBranches().size());
        
        // Display branches
        System.out.println("\n📋 Branch List:");
        library.getAllBranches().forEach(branch -> 
            System.out.println("   - " + branch.getBranchName() + " (" + branch.getBranchId() + ")")
        );
        
        // Add book to new branch
        Book book5 = new Book("978-0321125217", "Domain-Driven Design", "Eric Evans", 2003);
        library.addBook(book5, "BR002");
        
        // ✅ FIX: Return the book before transferring
        System.out.println("\n📥 Returning book before transfer...");
        try {
            library.returnBook("978-0134685991", "P001");
        } catch (Exception e) {
            System.out.println("⚠️ Book already returned or not checked out");
        }
        
        // Transfer book between branches
        System.out.println("\n🔄 Transferring book between branches...");
        try {
            // library.transferBook("978-0134685991", "BR001", "BR002");
            library.transferBook("978-0596007126", "BR001", "BR002");
        } catch (Exception e) {
            System.out.println("❌ Transfer failed: " + e.getMessage());
        }
        
        // Check branch inventories
        System.out.println("\n📚 Main Library Inventory: " + 
                        library.getBranchInventory("BR001").size() + " books");
        System.out.println("📚 Downtown Library Inventory: " + 
                        library.getBranchInventory("BR002").size() + " books");
        
        // Search across branches
        System.out.println("\n🔍 Searching 'Design' across all branches:");
        Map<String, List<Book>> results = library.searchBookAcrossBranches("Design");
        results.forEach((branchName, books) -> {
            System.out.println("   " + branchName + ":");
            books.forEach(book -> System.out.println("      - " + book.getTitle()));
        });
        
        System.out.println("\n✅ Multi-Branch Support Demo Completed");
    }
    /**
     * Demo 6: Recommendation System.
     */
    private static void demoRecommendationSystem(LibraryManagementSystem library) {
        System.out.println("\n" + "-".repeat(60));
        System.out.println("💡 DEMO 6: RECOMMENDATION SYSTEM");
        System.out.println("-".repeat(60));
        
        // Get recommendations for patron based on history
        System.out.println("\n💡 Personalized recommendations for Alice (P001):");
        List<Book> recommendations = library.getRecommendations("P001", 3);
        if (recommendations.isEmpty()) {
            System.out.println("   No recommendations available yet");
        } else {
            recommendations.forEach(book -> 
                System.out.println("   - " + book.getTitle() + " by " + book.getAuthor())
            );
        }
        
        // Get popular books
        System.out.println("\n🔥 Most Popular Books:");
        List<Book> popularBooks = library.getPopularBooks(3);
        popularBooks.forEach(book -> 
            System.out.println("   - " + book.getTitle() + " by " + book.getAuthor())
        );
        
        // Get similar books
        System.out.println("\n📚 Books similar to 'Clean Code':");
        List<Book> similarBooks = library.getSimilarBooks("978-0132350884", 2);
        if (similarBooks.isEmpty()) {
            System.out.println("   No similar books found");
        } else {
            similarBooks.forEach(book -> 
                System.out.println("   - " + book.getTitle() + " by " + book.getAuthor())
            );
        }
        
        System.out.println("\n✅ Recommendation System Demo Completed");
    }
    
    /**
     * Demo 7: Design Patterns Showcase.
     */
    private static void demoDesignPatterns() {
        System.out.println("\n" + "-".repeat(60));
        System.out.println("🎨 DEMO 7: DESIGN PATTERNS SHOWCASE");
        System.out.println("-".repeat(60));
        
        // Factory Pattern
        System.out.println("\n🏭 Factory Pattern:");
        System.out.println("   Creating library items using Factory...");
        var bookItem = LibraryItemFactory.createBook("978-1234567890", "Test Book", "Test Author", 2024);
        var magazineItem = LibraryItemFactory.createMagazine("MAG-2024-01", "Tech Monthly");
        System.out.println("   ✅ Created: " + bookItem.getItemType() + " - " + bookItem.getTitle());
        System.out.println("   ✅ Created: " + magazineItem.getItemType() + " - " + magazineItem.getTitle());
        
        // Strategy Pattern
        System.out.println("\n📊 Strategy Pattern:");
        System.out.println("   Calculating late fees using different strategies...");
        System.out.println("   Book (10 days late): $" + bookItem.calculateLateFee(10));
        System.out.println("   Magazine (10 days late): $" + magazineItem.calculateLateFee(10));
        
        // Observer Pattern
        System.out.println("\n👁️ Observer Pattern:");
        System.out.println("   Demonstrated in Reservation System");
        System.out.println("   Patrons are notified when reserved books become available");
        
        System.out.println("\n✅ Design Patterns Demo Completed");
    }
}