package linkedin.entities;

import linkedin.enums.NotificationType;

import java.time.LocalDateTime;
import java.util.UUID;

public class Notification {
    private final String id;
    private final String memberId; // The ID of the member to notify
    private final NotificationType type;
    private final String content;
    private final LocalDateTime createdAt;
    private boolean isRead = false;

    public Notification(String memberId, NotificationType type, String content) {
        this.id = UUID.randomUUID().toString();
        this.memberId = memberId;
        this.type = type;
        this.content = content;
        this.createdAt = LocalDateTime.now();
    }

    public String getContent() { return content; }
    public void markAsRead() { this.isRead = true; }
    public boolean isRead() { return isRead; }
}
