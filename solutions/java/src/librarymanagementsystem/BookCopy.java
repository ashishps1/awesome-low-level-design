package librarymanagementsystem;

import java.util.UUID;

public class BookCopy {
    private final String id;
    private final Book book;
    private boolean isAvailable;

    public BookCopy(Book book) {
        this.id = UUID.randomUUID().toString();
        this.book = book;
        this.isAvailable = true;
    }

    public synchronized boolean isAvailable() {
        return isAvailable;
    }

    public synchronized void markIssued() {
        if (!isAvailable) throw new IllegalStateException("Already issued");
        isAvailable = false;
    }

    public synchronized void markReturned() {
        isAvailable = true;
    }

    public Book getBook() {
        return book;
    }

    public String getId() {
        return id;
    }
}
