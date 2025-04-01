package loggingframework.logappender;

import loggingframework.LogMessage;

public interface LogAppender {
    void append(LogMessage logMessage);
}
