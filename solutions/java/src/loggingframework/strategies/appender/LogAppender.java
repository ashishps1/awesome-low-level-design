package loggingframework.strategies.appender;

import loggingframework.entities.LogMessage;
import loggingframework.strategies.formatter.LogFormatter;

public interface LogAppender {
    void append(LogMessage logMessage);
    void close();
    LogFormatter getFormatter();
    void setFormatter(LogFormatter formatter);
}
