package librarymanagementsystem;

import java.util.UUID;

public class BookCopy {
    private final String barCode;
    private final Book book;
    private BookStatus status;

    public BookCopy(Book book) {
        this.barCode = UUID.randomUUID().toString();
        this.book = book;
        this.status = BookStatus.AVAILABLE;
    }

    public synchronized boolean isAvailable() {
        return status == BookStatus.AVAILABLE;
    }

    public synchronized void markBorrowed() {
        if (!isAvailable()) throw new IllegalStateException("Already issued");
        status = BookStatus.BORROWED;
    }

    public synchronized void markAvailable() {
        status = BookStatus.AVAILABLE;
    }

    public Book getBook() {
        return book;
    }

    public String getBarCode() {
        return barCode;
    }
}
