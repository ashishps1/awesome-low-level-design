package librarymanagementsystem;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class LibraryManagementSystem {
    private static LibraryManagementSystem instance;
    private final Catalog catalog;
    private final Map<String, Member> members;
    private final Map<String, Loan> loans;

    private LibraryManagementSystem() {
        catalog = new Catalog();
        members = new ConcurrentHashMap<>();
        loans = new ConcurrentHashMap<>();
    }

    public static synchronized LibraryManagementSystem getInstance() {
        if (instance == null) {
            instance = new LibraryManagementSystem();
        }
        return instance;
    }

    public void addBook(Book book) {
        BookCopy copy = new BookCopy(book);
        catalog.add(copy);
    }

    public Member registerMember(String name, String contactInfo) {
        Member member = new Member(name, contactInfo);
        members.put(member.getId(), member);
        return member;
    }

    public synchronized Loan borrowBook(String memberId, String title) {
        Member member = members.get(memberId);
        if (member == null || !member.canBorrow()) throw new RuntimeException("Not allowed to borrow");

        List<BookCopy> copies = catalog.getBookCopiesByTitle(title);
        for (BookCopy copy : copies) {
            if (copy.isAvailable()) {
                copy.markIssued();
                Loan loan = new Loan(copy, member);
                member.addLoan(loan);
                loans.put(loan.getId(), loan);
                System.out.println("Book borrowed: " + copy.getBook().getTitle() + " by " + member.getName());
                return loan;
            }
        }

        throw new RuntimeException("No available copy");
    }

    public synchronized void returnBook(String loanId) {
        Loan loan = loans.get(loanId);
        loan.closeLoan();
    }

    public List<Book> searchByTitle(String title) {
        return catalog.searchByTitle(title);
    }

    public List<Book> searchByAuthor(String author) {
        return catalog.searchByAuthor(author);
    }
}
