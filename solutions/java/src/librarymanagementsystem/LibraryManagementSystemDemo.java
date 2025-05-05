package librarymanagementsystem;

import java.util.List;

public class LibraryManagementSystemDemo {
    public static void run() {
        LibraryManagementSystem libraryManagementSystem = LibraryManagementSystem.getInstance();

        // Add books to the catalog
        libraryManagementSystem.addBook(new Book("ISBN1", "Book 1", "Author 1"));
        libraryManagementSystem.addBook(new Book("ISBN2", "Book 2", "Author 1"));
        libraryManagementSystem.addBook(new Book("ISBN3", "Book 3", "Author 3"));

        // Register members
        Member member1 = libraryManagementSystem.registerMember("John Doe", "john@example.com");
        Member member2 = libraryManagementSystem.registerMember("Jane Smith", "jane@example.com");

        // Borrow books
        Loan loan1 = libraryManagementSystem.borrowBook(member1.getId(), "Book 1");
        Loan loan2 = libraryManagementSystem.borrowBook(member2.getId(), "Book 2");

        // Return books
        libraryManagementSystem.returnBook(loan1.getId());

        // Search books
        List<Book> searchResults = libraryManagementSystem.searchByAuthor("Author 1");
        System.out.println("Search Results:");
        for (Book book : searchResults) {
            System.out.println(book.getTitle() + " by " + book.getAuthor());
        }
    }
}
