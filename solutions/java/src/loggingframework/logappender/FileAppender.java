package loggingframework.logappender;

import loggingframework.LogFormatter;
import loggingframework.LogMessage;

import java.io.FileWriter;
import java.io.IOException;

public class FileAppender implements LogAppender {
    private FileWriter writer;
    private final LogFormatter formatter;

    public FileAppender(String filePath, LogFormatter formatter) {
        this.formatter = formatter;
        try {
            this.writer = new FileWriter(filePath, true);
        } catch (Exception e) {
            System.out.println("Failed to create writer for file logs, exception: " + e.getMessage());
        }
    }

    @Override
    public synchronized void append(LogMessage logMessage) {
        try {
            writer.write(formatter.format(logMessage) + "\n");
            writer.flush();
        } catch (IOException e) {
            System.out.println("Failed to write logs to file, exception: " + e.getMessage());
        }
    }
}
