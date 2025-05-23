public class IteratorDemo {
    public static void main(String[] args) {
        BookShelf bookShelf = new BookShelf();
        bookShelf.addBook(new Book("Design Patterns"));
        bookShelf.addBook(new Book("Clean Code"));
        bookShelf.addBook(new Book("Refactoring"));

        Iterator<Book> iterator = bookShelf.getIterator();
        System.out.println("Books in the shelf:");
        while (iterator.hasNext()) {
            Book book = iterator.next();
            System.out.println("- " + book.getTitle());
        }
    }
}