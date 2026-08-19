// BookNotAvailableException.java
package librarymanagementsystem.exceptions;

public class BookNotAvailableException extends RuntimeException {
    public BookNotAvailableException(String message) {
        super(message);
    }
}