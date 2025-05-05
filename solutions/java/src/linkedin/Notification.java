package linkedin;

import java.util.Date;
import java.util.UUID;

public class Notification {
    private final String id;
    private final User user;
    private final NotificationType type;
    private final String content;
    private final Date timestamp;

    public Notification(User user, NotificationType type, String content) {
        this.id = UUID.randomUUID().toString();
        this.user = user;
        this.type = type;
        this.content = content;
        this.timestamp = new Date();
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
}
