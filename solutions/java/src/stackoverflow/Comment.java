package stackoverflow;

import java.util.Date;

public class Comment {
    private final int id;
    private final String content;
    private final User author;
    private final Date creationDate;

    public Comment(User author, String content) {
        this.id = generateId();
        this.author = author;
        this.content = content;
        this.creationDate = new Date();
    }

    private int generateId() {
        return (int) (System.currentTimeMillis() % Integer.MAX_VALUE);
    }

    // Getters
    public int getId() { return id; }
    public User getAuthor() { return author; }
    public String getContent() { return content; }
    public Date getCreationDate() { return creationDate; }
}