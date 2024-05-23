package librarymanagementsystem;

import java.util.ArrayList;
import java.util.List;

public class Member {
    private final String memberId;
    private final String name;
    private final String contactInfo;
    private final List<Book> borrowedBooks;

    public Member(String memberId, String name, String contactInfo) {
        this.memberId = memberId;
        this.name = name;
        this.contactInfo = contactInfo;
        this.borrowedBooks = new ArrayList<>();
    }

    public void borrowBook(Book book) {
        borrowedBooks.add(book);
    }

    public void returnBook(Book book) {
        borrowedBooks.remove(book);
    }

    public String getMemberId() {
        return memberId;
    }

    public String getName() {
        return name;
    }

    public List<Book> getBorrowedBooks() {
        return borrowedBooks;
    }
}
