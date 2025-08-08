package socialnetworkingservice.model;

import java.time.LocalDateTime;
import java.util.*;

public abstract class CommentableEntity {
    protected final String id;
    protected final User author;
    protected final String content;
    protected final LocalDateTime timestamp;
    private final Set<User> likes = new HashSet<>();
    protected final List<Comment> comments = new ArrayList<>();

    public CommentableEntity(User author, String content) {
        this.id = UUID.randomUUID().toString();
        this.author = author;
        this.content = content;
        this.timestamp = LocalDateTime.now();
    }

    public void addLike(User user) {
        likes.add(user);
    }

    public void addComment(Comment comment) {
        comments.add(comment);
    }

    public String getId() { return id; }
    public User getAuthor() { return author; }
    public String getContent() { return content; }
    public LocalDateTime getTimestamp() { return timestamp; }
    public List<Comment> getComments() { return comments; }
    public Set<User> getLikes() {
        return likes;
    }
}