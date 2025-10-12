package loggingframework.entities;

import loggingframework.enums.LogLevel;

import java.time.LocalDateTime;

public final class LogMessage {
    private final LocalDateTime timestamp;
    private final LogLevel level;
    private final String loggerName;
    private final String threadName;
    private final String message;

    public LogMessage(LogLevel level, String loggerName, String message) {
        this.timestamp = LocalDateTime.now();
        this.level = level;
        this.loggerName = loggerName;
        this.message = message;
        this.threadName = Thread.currentThread().getName();
    }

    // Getters for all fields
    public LocalDateTime getTimestamp() { return timestamp; }
    public LogLevel getLevel() { return level; }
    public String getLoggerName() { return loggerName; }
    public String getThreadName() { return threadName; }
    public String getMessage() { return message; }
}
