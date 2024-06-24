class BookShelf implements Container<Book> {
    private List<Book> books;

    public BookShelf() {
        books = new ArrayList<>();
    }

    public void addBook(Book book) {
        books.add(book);
    }

    @Override
    public Iterator<Book> getIterator() {
        return new BookShelfIterator();
    }

    // ConcreteIterator
    private class BookShelfIterator implements Iterator<Book> {
        private int index;

        @Override
        public boolean hasNext() {
            return index < books.size();
        }

        @Override
        public Book next() {
            if (this.hasNext()) {
                return books.get(index++);
            }
            return null;
        }
    }
}