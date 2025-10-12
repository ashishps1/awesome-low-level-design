package loggingframework.strategies.formatter;

import loggingframework.entities.LogMessage;

public interface LogFormatter {
    String format(LogMessage logMessage);
}
