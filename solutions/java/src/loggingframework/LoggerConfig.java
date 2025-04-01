package loggingframework;

import loggingframework.logappender.LogAppender;

public class LoggerConfig {
    private LogLevel logLevel;
    private LogAppender logAppender;

    public LoggerConfig(LogLevel logLevel, LogAppender logAppender) {
        this.logLevel = logLevel;
        this.logAppender = logAppender;
    }

    public LogLevel getLogLevel() {
        return logLevel;
    }

    public void setLogLevel(LogLevel logLevel) {
        this.logLevel = logLevel;
    }

    public LogAppender getLogAppender() {
        return logAppender;
    }

    public void setLogAppender(LogAppender logAppender) {
        this.logAppender = logAppender;
    }
}
