package librarymanagementsystem;

import java.util.List;

public class LibraryManagementSystemDemo {
    public static void run() {
        LibraryManagementSystem libraryManagementSystem = LibraryManagementSystem.getInstance();

        // Add books to the catalog
        BookCopy copy1 = libraryManagementSystem.addBookCopy("ISBN1", "Book 1", "Author 1");
        BookCopy copy2 = libraryManagementSystem.addBookCopy("ISBN2", "Book 2", "Author 1");
        BookCopy copy3 = libraryManagementSystem.addBookCopy("ISBN3", "Book 3", "Author 3");

        // Register members
        Member member1 = libraryManagementSystem.registerMember("John Doe", "john@example.com");
        Member member2 = libraryManagementSystem.registerMember("Jane Smith", "jane@example.com");

        // Borrow books
        libraryManagementSystem.borrowBook(member1.getId(), copy1.getBarCode());
        libraryManagementSystem.borrowBook(member2.getId(), copy2.getBarCode());

        // Return books
        libraryManagementSystem.returnBook(member1.getId(), copy1.getBarCode());

        // Search books
        List<Book> searchResults = libraryManagementSystem.searchByAuthor("Author 1");
        System.out.println("Search Results for Author1:");
        for (Book book : searchResults) {
            System.out.println(book.getTitle() + " by " + book.getAuthor());
        }
    }
}
