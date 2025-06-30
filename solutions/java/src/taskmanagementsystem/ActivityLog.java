package taskmanagementsystem;

import java.util.Date;
import java.util.UUID;

public class ActivityLog {
    private final String logId;
    private final String action;
    private final User performedBy;
    private final Date timestamp;

    public ActivityLog(String action, User performedBy) {
        this.logId = UUID.randomUUID().toString();
        this.action = action;
        this.performedBy = performedBy;
        this.timestamp = new Date();
    }
}
