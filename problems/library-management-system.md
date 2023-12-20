# Designing a Library Management System

This contains the object-oriented design and implementation of a Library Management System (LMS) using Java.

The LMS is designed to manage library operations, including book inventory, member subscriptions, and book lending processes, using Java's object-oriented features.

## System Requirements
The LMS supports:
1. **Book Inventory Management:** Add, update, and remove books.
2. **Membership Management:** Manage library member information.
3. **Book Lending:** Handle book checkouts and returns.
4. **Search Functionality:** Enable searching for books.

## Core Use Cases
- **Adding Books:** Librarians can add new books to the system.
- **Registering Members:** Register new library members.
- **Lending Books:** Check out books to members.
- **Returning Books:** Manage the return process.

## UML/Class Diagrams
Key classes include 
- `Library`: Manages the overall library operations.
- `Book`: Represents a book in the library.
- `Member`: Represents a library member.
- `Loan`: Manages the lending of books to members.

## Java Implementation

### Book Class
```java
public class Book {
    private String title;
    private String author;
    private String ISBN;
    private boolean isAvailable;

    public Book(String title, String author, String ISBN) {
        this.title = title;
        this.author = author;
        this.ISBN = ISBN;
        this.isAvailable = true;
    }

    // Getters and setters...
}
```
### Member Class
```java
import java.util.ArrayList;
import java.util.List;

public class Member {
    private String name;
    private String memberId;
    private List<Loan> loans;

    public Member(String name) {
        this.name = name;
        this.memberId = generateMemberId();
        this.loans = new ArrayList<>();
    }

    private String generateMemberId() {
        // Generate a unique member ID
        return "MEM" + System.currentTimeMillis();
    }

    // Add loan to member's record
    public void addLoan(Loan loan) {
        loans.add(loan);
    }

    // Getters and setters...
}
```
### Loan Class
```java
import java.time.LocalDate;

public class Loan {
    private Book book;
    private Member member;
    private LocalDate issueDate;
    private LocalDate dueDate;

    public Loan(Book book, Member member) {
        this.book = book;
        this.member = member;
        this.issueDate = LocalDate.now();
        this.dueDate = issueDate.plusDays(14); // 2-week loan period
        book.setIsAvailable(false);
        member.addLoan(this);
    }

    // Return a book
    public void returnBook() {
        book.setIsAvailable(true);
        // Remove this loan from member's record
        member.getLoans().remove(this);
    }

    // Getters and setters...
}
```
### Library Class
```java
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Library {
    private List<Book> books;
    private List<Member> members;

    public Library() {
        books = new ArrayList<>();
        members = new ArrayList<>();
    }

    // Add a new book to the library
    public void addBook(Book book) {
        books.add(book);
    }

    // Register a new member
    public void registerMember(Member member) {
        members.add(member);
    }

    // Lend a book to a member
    public void lendBook(String ISBN, Member member) {
        Book book = books.stream()
                         .filter(b -> b.getISBN().equals(ISBN) && b.isAvailable())
                         .findFirst().orElse(null);
        if (book != null) {
            new Loan(book, member);
        }
    }

    // Search for books by title
    public List<Book> searchBooksByTitle(String title) {
        return books.stream()
                    .filter(book -> book.getTitle().contains(title))
                    .collect(Collectors.toList());
    }

    // Other necessary methods...
}
```