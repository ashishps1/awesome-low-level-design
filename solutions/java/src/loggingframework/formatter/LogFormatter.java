package loggingframework.formatter;

import loggingframework.LogMessage;

public interface LogFormatter {
    String format(LogMessage message);
}
