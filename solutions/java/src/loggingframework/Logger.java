package loggingframework;

import loggingframework.entities.LogMessage;
import loggingframework.enums.LogLevel;
import loggingframework.strategies.appender.LogAppender;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class Logger {
    private final String name;
    private LogLevel level;
    private final Logger parent;
    private final List<LogAppender> appenders;
    private boolean additivity = true;

    Logger(String name, Logger parent) {
        this.name = name;
        this.parent = parent;
        this.appenders = new CopyOnWriteArrayList<>();
    }

    public void addAppender(LogAppender appender) {
        appenders.add(appender);
    }

    public List<LogAppender> getAppenders() {
        return appenders;
    }

    public void setLevel(LogLevel minLevel) {
        this.level = minLevel;
    }

    public void setAdditivity(boolean additivity) {
        this.additivity = additivity;
    }

    public LogLevel getEffectiveLevel() {
        for (Logger logger = this; logger != null; logger = logger.parent) {
            LogLevel currentLevel = logger.level;
            if (currentLevel != null) {
                return currentLevel;
            }
        }
        return LogLevel.DEBUG; // Default root level
    }

    public void log(LogLevel messageLevel, String message) {
        if (messageLevel.isGreaterOrEqual(getEffectiveLevel())) {
            LogMessage logMessage = new LogMessage(messageLevel, this.name, message);
            callAppenders(logMessage);
        }
    }

    private void callAppenders(LogMessage logMessage) {
        if (!appenders.isEmpty()) {
            LogManager.getInstance().getProcessor().process(logMessage, this.appenders);
        }
        if (additivity && parent != null) {
            parent.callAppenders(logMessage);
        }
    }

    public void debug(String message) {
        log(LogLevel.DEBUG, message);
    }
    public void info(String message) {
        log(LogLevel.INFO, message);
    }
    public void warn(String message) {
        log(LogLevel.WARN, message);
    }
    public void error(String message) {
        log(LogLevel.ERROR, message);
    }
    public void fatal(String message) {
        log(LogLevel.FATAL, message);
    }
}
