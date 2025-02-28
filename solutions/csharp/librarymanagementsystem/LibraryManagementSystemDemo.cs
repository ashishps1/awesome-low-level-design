using System;
using System.Collections.Generic;

namespace LibraryManagementSystem
{
    public class LibraryManagementSystemDemo
    {
        public static void Run()
        {
            LibraryManager libraryManager = LibraryManager.GetInstance();

            // Add books to the catalog
            libraryManager.AddBook(new Book("ISBN1", "Book 1", "Author 1", 2020));
            libraryManager.AddBook(new Book("ISBN2", "Book 2", "Author 2", 2019));
            libraryManager.AddBook(new Book("ISBN3", "Book 3", "Author 3", 2021));

            // Register members
            libraryManager.RegisterMember(new Member("M1", "John Doe", "john@example.com"));
            libraryManager.RegisterMember(new Member("M2", "Jane Smith", "jane@example.com"));

            // Borrow books
            libraryManager.BorrowBook("M1", "ISBN1");
            libraryManager.BorrowBook("M2", "ISBN2");

            // Return books
            libraryManager.ReturnBook("M1", "ISBN1");

            // Search books
            List<Book> searchResults = libraryManager.SearchBooks("Book");
            Console.WriteLine("Search Results:");
            foreach (Book book in searchResults)
            {
                Console.WriteLine($"{book.Title} by {book.Author}");
            }
        }
    }
}