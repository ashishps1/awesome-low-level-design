package librarymanagementsystem;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class LibraryManagementSystem {
    private static LibraryManagementSystem instance;
    private final Catalog catalog;
    private final Map<String, Book> books;
    private final Map<String, Member> members;
    private final Map<String, Loan> loans;
    private static final int MAX_BOOKS_PER_MEMBER = 5;

    private LibraryManagementSystem() {
        catalog = new Catalog();
        books = new ConcurrentHashMap<>();
        members = new ConcurrentHashMap<>();
        loans = new ConcurrentHashMap<>();
    }

    public static synchronized LibraryManagementSystem getInstance() {
        if (instance == null) {
            instance = new LibraryManagementSystem();
        }
        return instance;
    }

    public BookCopy addBookCopy(String isbn, String title, String authorName) {
        Book book = books.getOrDefault(isbn, new Book(isbn, title, authorName));
        books.put(book.getIsbn(), book);
        BookCopy copy = new BookCopy(book);
        catalog.add(copy);
        return copy;
    }

    public Member registerMember(String name, String contactInfo) {
        Member member = new Member(name, contactInfo);
        members.put(member.getId(), member);
        return member;
    }

    public synchronized boolean borrowBook(String memberId, String barcode) {
        Member member = members.get(memberId);
        BookCopy bookCopy = catalog.getBookCopyByBarcode(barcode);

        if (member == null || bookCopy == null) {
            System.out.println("Error: Invalid member or book.");
            return false;
        }

        if (member.getBorrowedCount() >= MAX_BOOKS_PER_MEMBER) {
            System.out.println("Error: Member has reached the borrowing limit\n");
            return false;
        }

        bookCopy.markBorrowed();
        Loan loan = new Loan(bookCopy, member);
        member.addLoan(loan);
        loans.put(loan.getId(), loan);

        System.out.printf("Successfully borrowed %s by %s\n", bookCopy.getBook().getTitle(), member.getName());

        return true;
    }

    public synchronized boolean returnBook(String memberId, String barcode) {
        Member member = members.get(memberId);
        BookCopy bookCopy = catalog.getBookCopyByBarcode(barcode);

        if (member == null || bookCopy == null) {
            System.out.println("Error: Invalid member or book.");
            return false;
        }

        Loan loanToRemove = member.getLoans().stream()
                .filter(loan -> loan.getCopy().getBarCode().equals(barcode))
                .findFirst()
                .orElse(null);


        if (loanToRemove != null) {
            member.removeLoan(loanToRemove);
            bookCopy.markAvailable();
            System.out.printf("Successfully returned %s by %s\n", bookCopy.getBook().getTitle(), member.getName());
            return true;
        }

        return false;
    }

    public List<Book> searchByTitle(String title) {
        return catalog.searchByTitle(title);
    }

    public List<Book> searchByAuthor(String author) {
        return catalog.searchByAuthor(author);
    }
}
