package socialnetworkingservice;

import java.sql.Timestamp;
import java.util.List;

public class Post {
    private String id;
    private String userId;
    private String content;
    private List<String> imageUrls;
    private List<String> videoUrls;
    private Timestamp timestamp;
    private List<String> likes;
    private List<Comment> comments;

    public Post(String id, String userId, String content, List<String> imageUrls, List<String> videoUrls, Timestamp timestamp, List<String> likes, List<Comment> comments) {
        this.id = id;
        this.userId = userId;
        this.content = content;
        this.imageUrls = imageUrls;
        this.videoUrls = videoUrls;
        this.timestamp = timestamp;
        this.likes = likes;
        this.comments = comments;
    }

    public String getId() {
        return id;
    }

    public String getUserId() {
        return userId;
    }

    public String getContent() {
        return content;
    }

    public List<String> getImageUrls() {
        return imageUrls;
    }

    public List<String> getVideoUrls() {
        return videoUrls;
    }

    public Timestamp getTimestamp() {
        return timestamp;
    }

    public List<String> getLikes() {
        return likes;
    }

    public List<Comment> getComments() {
        return comments;
    }
}
