package linkedin;

import java.sql.Timestamp;

public class Notification {
    private final String id;
    private final User user;
    private final NotificationType type;
    private final String content;
    private final Timestamp timestamp;

    public Notification(String id, User user, NotificationType type, String content, Timestamp timestamp) {
        this.id = id;
        this.user = user;
        this.type = type;
        this.content = content;
        this.timestamp = timestamp;
    }

    public String getId() {
        return id;
    }

    public User getUser() {
        return user;
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
