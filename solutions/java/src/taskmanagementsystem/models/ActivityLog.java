package taskmanagementsystem.models;

import java.time.LocalDateTime;

public class ActivityLog {
    private final String description;
    private final LocalDateTime timestamp;

    public ActivityLog(String description) {
        this.description = description;
        this.timestamp = LocalDateTime.now();
    }

    @Override
    public String toString() {
        return "[" + timestamp + "] " + description;
    }
}
