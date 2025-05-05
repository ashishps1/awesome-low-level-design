package socialnetworkingservice;

import java.sql.Timestamp;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class Post {
    private final String id;
    private final User author;
    private final String content;
    private final Timestamp timestamp;
    private final Map<String, Like> userIdLikeMap;
    private final List<Comment> comments;

    public Post(User author, String content) {
        this.id = UUID.randomUUID().toString();
        this.author = author;
        this.content = content;
        this.timestamp = new Timestamp(System.currentTimeMillis());
        this.userIdLikeMap = new ConcurrentHashMap<>();
        this.comments = Collections.synchronizedList(new ArrayList<>());;
    }

    public synchronized void like(User user) {
        if(!userIdLikeMap.containsKey(user.getId())) {
            userIdLikeMap.put(user.getId(), new Like(user));
        } else {
            // unlike if already liked
            userIdLikeMap.remove(user.getId());
        }
    }

    public void comment(User user, String text) {
        comments.add(new Comment(user, text));
    }

    public int getLikeCount() {
        return userIdLikeMap.size();
    }

    public List<Like> getLikes() {
        return userIdLikeMap.values().stream().toList();
    }

    public int getCommentCount() {
        return comments.size();
    }

    public List<Comment> getComments() {
        return comments;
    }

    public String getId() {
        return id;
    }

    public User getAuthor() {
        return author;
    }

    public String getContent() {
        return content;
    }

    public Timestamp getTimestamp() {
        return timestamp;
    }
}
