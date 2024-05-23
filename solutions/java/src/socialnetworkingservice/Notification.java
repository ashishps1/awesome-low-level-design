package socialnetworkingservice;

import java.sql.Timestamp;

public class Notification {
    private String id;
    private String userId;
    private NotificationType type;
    private String content;
    private Timestamp timestamp;

    public Notification(String id, String userId, NotificationType type, String content, Timestamp timestamp) {
        this.id = id;
        this.userId = userId;
        this.type = type;
        this.content = content;
        this.timestamp = timestamp;
    }

    public String getId() {
        return id;
    }

    public String getUserId() {
        return userId;
    }

    public NotificationType getType() {
        return type;
    }

    public String getContent() {
        return content;
    }

    public Timestamp getTimestamp() {
        return timestamp;
    }
}
