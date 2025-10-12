package librarymanagementsystem.models;

public class Magazine extends LibraryItem {
    private final String publisher;

    public Magazine(String id, String title, String publisher) {
        super(id, title);
        this.publisher = publisher;
    }

    @Override
    public String getAuthorOrPublisher() { return publisher; }
}
