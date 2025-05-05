package socialnetworkingservice;

import java.sql.Timestamp;
import java.util.UUID;

public class Notification {
    private final String id;
    private final User user;
    private final NotificationType type;
    private final String content;
    private final Timestamp timestamp;

    public Notification(User user, NotificationType type, String content) {
        this.id = UUID.randomUUID().toString();
        this.user = user;
        this.type = type;
        this.content = content;
        this.timestamp = new Timestamp(System.currentTimeMillis());
    }

    public String getId() {
        return id;
    }

    public String getUserId() {
        return user.getId();
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
