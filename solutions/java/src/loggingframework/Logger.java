package loggingframework;

import loggingframework.logappender.ConsoleAppender;

public class Logger {
    private static final Logger instance = new Logger();
    private LoggerConfig config;

    private Logger() {
        // Private constructor to enforce singleton pattern
        config = new LoggerConfig(LogLevel.INFO, new ConsoleAppender());
    }

    public static Logger getInstance() {
        return instance;
    }

    public void setConfig(LoggerConfig config) {
        this.config = config;
    }

    public void log(LogLevel level, String message) {
        if (level.ordinal() >= config.getLogLevel().ordinal()) {
            LogMessage logMessage = new LogMessage(level, message);
            config.getLogAppender().append(logMessage);
        }
    }

    public void debug(String message) {
        log(LogLevel.DEBUG, message);
    }

    public void info(String message) {
        log(LogLevel.INFO, message);
    }

    public void warning(String message) {
        log(LogLevel.WARNING, message);
    }

    public void error(String message) {
        log(LogLevel.ERROR, message);
    }

    public void fatal(String message) {
        log(LogLevel.FATAL, message);
    }
}
