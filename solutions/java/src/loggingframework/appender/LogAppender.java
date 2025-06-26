package loggingframework.appender;

import loggingframework.LogMessage;

public interface LogAppender {
    void append(LogMessage logMessage);
}
