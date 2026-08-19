package librarymanagementsystem.models;

import java.util.*;

/**
 * Represents a library branch.
 * Follows SRP - Only handles branch-related data
 */
public class Branch {
    private final String branchId;
    private String branchName;
    private String address;
    private Map<String, Book> inventory; // ISBN -> Book
    
    public Branch(String branchId, String branchName, String address) {
        this.branchId = branchId;
        this.branchName = branchName;
        this.address = address;
        this.inventory = new HashMap<>();
    }
    
    // Getters
    public String getBranchId() { return branchId; }
    public String getBranchName() { return branchName; }
    public String getAddress() { return address; }
    
    public Map<String, Book> getInventory() {
        return Collections.unmodifiableMap(inventory);
    }
    
    // Setters
    public void setBranchName(String branchName) { this.branchName = branchName; }
    public void setAddress(String address) { this.address = address; }
    
    // Inventory management
    public void addBook(Book book) {
        inventory.put(book.getIsbn(), book);
        book.setCurrentBranchId(this.branchId);
    }
    
    public void removeBook(String isbn) {
        inventory.remove(isbn);
    }
    
    public Book getBook(String isbn) {
        return inventory.get(isbn);
    }
    
    public boolean hasBook(String isbn) {
        return inventory.containsKey(isbn);
    }
    
    public List<Book> getAllBooks() {
        return new ArrayList<>(inventory.values());
    }
    
    public List<Book> getAvailableBooks() {
        List<Book> available = new ArrayList<>();
        for (Book book : inventory.values()) {
            if (book.isAvailable()) {
                available.add(book);
            }
        }
        return available;
    }
    
    @Override
    public String toString() {
        return String.format("Branch{id='%s', name='%s', books=%d}",
                branchId, branchName, inventory.size());
    }
}