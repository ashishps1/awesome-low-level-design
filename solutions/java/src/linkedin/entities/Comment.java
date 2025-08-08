package linkedin.entities;

import java.time.LocalDateTime;

public class Comment {
    private final Member author;
    private final String text;
    private final LocalDateTime createdAt;

    public Comment(Member author, String text) {
        this.author = author;
        this.text = text;
        this.createdAt = LocalDateTime.now();
    }
    public Member getAuthor() { return author; }
    public String getText() { return text; }
}
