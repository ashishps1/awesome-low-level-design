// BookItem.java
package librarymanagementsystem.patterns.factory;

import librarymanagementsystem.models.Book;

/**
 * Concrete product - Book implementation.
 * Part of Factory Design Pattern
 */
public class BookItem implements LibraryItem {
    private final Book book;
    
    public BookItem(Book book) {
        this.book = book;
    }
    
    @Override
    public String getItemId() {
        return book.getIsbn();
    }
    
    @Override
    public String getTitle() {
        return book.getTitle();
    }
    
    @Override
    public String getItemType() {
        return "BOOK";
    }
    
    @Override
    public double calculateLateFee(int daysLate) {
        return daysLate * 0.50; // $0.50 per day for books
    }
    
    @Override
    public boolean isAvailable() {
        return book.isAvailable();
    }
    
    public Book getBook() {
        return book;
    }
}