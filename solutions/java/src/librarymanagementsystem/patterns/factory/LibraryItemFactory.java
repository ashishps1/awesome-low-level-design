package librarymanagementsystem.patterns.factory;

import librarymanagementsystem.models.Book;
import java.util.Map;

/**
 * Factory for creating library items.
 * Implements Factory Design Pattern
 * Follows OCP - Can add new item types without modifying existing code
 */
public class LibraryItemFactory {
    
    public static LibraryItem createItem(String type, Map<String, String> attributes) {
        if (type == null || attributes == null) {
            throw new IllegalArgumentException("Type and attributes cannot be null");
        }
        
        switch (type.toUpperCase()) {
            case "BOOK":
                Book book = new Book(
                    attributes.get("isbn"),
                    attributes.get("title"),
                    attributes.get("author"),
                    Integer.parseInt(attributes.getOrDefault("year", "2024"))
                );
                return new BookItem(book);
                
            case "MAGAZINE":
                return new MagazineItem(
                    attributes.get("issueNumber"),
                    attributes.get("title")
                );
                
            case "DVD":
                // Future extension - demonstrates OCP
                throw new UnsupportedOperationException("DVD not yet implemented");
                
            default:
                throw new IllegalArgumentException("Unknown item type: " + type);
        }
    }
    
    // Convenience methods
    public static LibraryItem createBook(String isbn, String title, String author, int year) {
        Map<String, String> attributes = Map.of(
            "isbn", isbn,
            "title", title,
            "author", author,
            "year", String.valueOf(year)
        );
        return createItem("BOOK", attributes);
    }
    
    public static LibraryItem createMagazine(String issueNumber, String title) {
        Map<String, String> attributes = Map.of(
            "issueNumber", issueNumber,
            "title", title
        );
        return createItem("MAGAZINE", attributes);
    }
}