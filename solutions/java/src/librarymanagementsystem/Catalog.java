package librarymanagementsystem;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class Catalog {
    private final Map<String, List<BookCopy>> byTitle = new HashMap<>();
    private final Map<String, List<BookCopy>> byAuthor = new HashMap<>();
    private final Map<String, List<BookCopy>> byIsbn = new HashMap<>();
    private final Map<String, BookCopy> bookCopiesByBarcode = new ConcurrentHashMap<>();

    public synchronized void add(BookCopy copy) {
        Book book = copy.getBook();
        byTitle.computeIfAbsent(book.getTitle().toLowerCase(), k -> new ArrayList<>()).add(copy);
        byAuthor.computeIfAbsent(book.getAuthor().toLowerCase(), k -> new ArrayList<>()).add(copy);
        byIsbn.computeIfAbsent(book.getIsbn(), k -> new ArrayList<>()).add(copy);
        bookCopiesByBarcode.put(copy.getBarCode(), copy);
    }

    public synchronized List<BookCopy> getBookCopiesByTitle(String title) {
        return byTitle.getOrDefault(title, List.of());
    }

    public BookCopy getBookCopyByBarcode(String barcode) {
        return bookCopiesByBarcode.get(barcode);
    }

    public synchronized List<Book> searchByTitle(String title) {
        return byTitle.getOrDefault(title.toLowerCase(), List.of()).stream()
                .map(BookCopy::getBook)
                .distinct()
                .toList();
    }

    public synchronized List<Book> searchByAuthor(String author) {
        return byAuthor.getOrDefault(author.toLowerCase(), List.of()).stream()
                .map(BookCopy::getBook)
                .distinct()
                .toList();
    }

    public synchronized List<Book> searchByIsbn(String isbn) {
        return byIsbn.getOrDefault(isbn, List.of()).stream()
                .map(BookCopy::getBook)
                .distinct()
                .toList();
    }
}
