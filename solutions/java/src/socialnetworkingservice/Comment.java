package socialnetworkingservice;

import java.sql.Timestamp;

public class Comment {
    private final String id;
    private final String userId;
    private final String postId;
    private final String content;
    private final Timestamp timestamp;

    public Comment(String id, String userId, String postId, String content, Timestamp timestamp) {
        this.id = id;
        this.userId = userId;
        this.postId = postId;
        this.content = content;
        this.timestamp = timestamp;
    }

    public String getId() {
        return id;
    }

    public String getUserId() {
        return userId;
    }

    public String getPostId() {
        return postId;
    }

    public String getContent() {
        return content;
    }

    public Timestamp getTimestamp() {
        return timestamp;
    }
}
