from library_manager import LibraryManager
from book import Book
from member import Member

class LibraryManagementSystemDemo:
    @staticmethod
    def run():
        library_manager = LibraryManager.get_instance()

        # Add books to the catalog
        library_manager.add_book(Book("ISBN1", "Book 1", "Author 1", 2020))
        library_manager.add_book(Book("ISBN2", "Book 2", "Author 2", 2019))
        library_manager.add_book(Book("ISBN3", "Book 3", "Author 3", 2021))

        # Register members
        library_manager.register_member(Member("M1", "John Doe", "john@example.com"))
        library_manager.register_member(Member("M2", "Jane Smith", "jane@example.com"))

        # Borrow books
        library_manager.borrow_book("M1", "ISBN1")
        library_manager.borrow_book("M2", "ISBN2")

        # Return books
        library_manager.return_book("M1", "ISBN1")

        # Search books
        search_results = library_manager.search_books("Book")
        print("Search Results:")
        for book in search_results:
            print(f"{book.title} by {book.author}")

if __name__ == "__main__":
    LibraryManagementSystemDemo.run()
