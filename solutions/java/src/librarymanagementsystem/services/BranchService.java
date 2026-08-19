package librarymanagementsystem.services;

import librarymanagementsystem.models.Book;
import librarymanagementsystem.models.Branch;
import librarymanagementsystem.repositories.BookRepository;
import librarymanagementsystem.exceptions.BookNotFoundException;

import java.util.*;

/**
 * Service for multi-branch library operations.
 * Follows SRP - Only handles branch-related business logic
 * Supports optional extension: Multi-branch Support
 */
public class BranchService {
    private final Map<String, Branch> branches;
    private final BookRepository bookRepository;
    
    public BranchService(BookRepository bookRepository) {
        this.branches = new HashMap<>();
        this.bookRepository = bookRepository;
    }
    
    /**
     * Add a new branch.
     */
    public void addBranch(Branch branch) {
        if (branches.containsKey(branch.getBranchId())) {
            throw new IllegalArgumentException("Branch already exists: " + branch.getBranchId());
        }
        branches.put(branch.getBranchId(), branch);
        System.out.println("✅ Branch added: " + branch.getBranchName());
    }
    
    /**
     * Get a branch by ID.
     */
    public Branch getBranch(String branchId) {
        Branch branch = branches.get(branchId);
        if (branch == null) {
            throw new IllegalArgumentException("Branch not found: " + branchId);
        }
        return branch;
    }
    
    /**
     * Get all branches.
     */
    public List<Branch> getAllBranches() {
        return new ArrayList<>(branches.values());
    }
    
    /**
     * Add a book to a specific branch.
     */
    public void addBookToBranch(Book book, String branchId) {
        Branch branch = getBranch(branchId);
        branch.addBook(book);
        book.setCurrentBranchId(branchId);
        bookRepository.save(book);
        System.out.println("✅ Book added to branch: " + book.getTitle() + " -> " + branch.getBranchName());
    }
    
    /**
     * Transfer a book between branches.
     */
    public void transferBook(String isbn, String fromBranchId, String toBranchId) {
        // Validate branches exist
        Branch fromBranch = getBranch(fromBranchId);
        Branch toBranch = getBranch(toBranchId);
        
        // Get the book
        Book book = bookRepository.findById(isbn)
                .orElseThrow(() -> new BookNotFoundException("Book not found: " + isbn));
        
        // Validate book is in source branch
        if (!book.getCurrentBranchId().equals(fromBranchId)) {
            throw new IllegalStateException("Book is not in the source branch");
        }
        
        // Validate book is available for transfer
        if (!book.isAvailable()) {
            throw new IllegalStateException("Book must be available (not checked out) for transfer");
        }
        
        // Perform transfer
        fromBranch.removeBook(isbn);
        toBranch.addBook(book);
        book.setCurrentBranchId(toBranchId);
        bookRepository.save(book);
        
        System.out.println("✅ Book transferred: " + book.getTitle());
        System.out.println("   From: " + fromBranch.getBranchName() + " -> To: " + toBranch.getBranchName());
    }
    
    /**
     * Get all books in a specific branch.
     */
    public List<Book> getBranchInventory(String branchId) {
        Branch branch = getBranch(branchId);
        return branch.getAllBooks();
    }
    
    /**
     * Get available books in a specific branch.
     */
    public List<Book> getAvailableBooksInBranch(String branchId) {
        Branch branch = getBranch(branchId);
        return branch.getAvailableBooks();
    }
    
    /**
     * Search for a book across all branches.
     */
    public Map<String, List<Book>> searchBookAcrossBranches(String query) {
        Map<String, List<Book>> results = new HashMap<>();
        
        for (Branch branch : branches.values()) {
            List<Book> branchBooks = branch.getAllBooks().stream()
                    .filter(book -> book.getTitle().toLowerCase().contains(query.toLowerCase()) ||
                                  book.getAuthor().toLowerCase().contains(query.toLowerCase()))
                    .toList();
            
            if (!branchBooks.isEmpty()) {
                results.put(branch.getBranchName(), branchBooks);
            }
        }
        
        return results;
    }
}