package loggingframework.logappender;

import loggingframework.LogMessage;

public class ConsoleAppender implements LogAppender {
    @Override
    public void append(LogMessage logMessage) {
        System.out.println(logMessage);
    }
}
