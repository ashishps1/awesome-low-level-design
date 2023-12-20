# Designing a Logging Framework

In this blog post, we will explore the design and development of a Logging Framework in Java, using object-oriented programming principles. 

A Logging Framework is crucial for effective monitoring, debugging, and auditing of applications.

## System Requirements

The Logging Framework should:

1. **Support Multiple Log Levels:** Including INFO, DEBUG, WARN, and ERROR.
2. **Flexible Log Destination:** Enable logging to various outputs like the console, files, or external services.
3. **Configurable Formatting:** Allow for custom log message formats.
4. **Performance Efficiency:** Ensure minimal impact on application performance.

## Core Use Cases

1. **Logging Messages:** Ability to log messages at different levels.
2. **Configuring Loggers:** Setup loggers with varying settings and outputs.
3. **Managing Log Output:** Direct messages to appropriate destinations based on configurations.

## UML/Class Diagrams

Key Classes:

- `Logger`: Main interface for logging messages.
- `LogLevel`: Enum representing log levels.
- `LogDestination`: Interface for different log output destinations.
- `ConsoleDestination`, `FileDestination`: Implementations of the `LogDestination` interface.

## Java Implementation

### LogLevel Enum

Defines different levels of logging.

```java
public enum LogLevel {
    INFO, DEBUG, WARN, ERROR
}
```
### LogDestination Interface
Interface for different log destinations.
```java
public interface LogDestination {
    void writeLog(String message);
}
```
### ConsoleDestination Class
Implementation for logging to the console.
```java
public class ConsoleDestination implements LogDestination {
    @Override
    public void writeLog(String message) {
        System.out.println(message);
    }
}
```
### FileDestination Class
Implementation for logging to a file.
```java
import java.io.FileWriter;
import java.io.IOException;

public class FileDestination implements LogDestination {
    private String filename;

    public FileDestination(String filename) {
        this.filename = filename;
    }

    @Override
    public void writeLog(String message) {
        try (FileWriter fileWriter = new FileWriter(filename, true)) {
            fileWriter.write(message + "\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
```
### Logger Class
Main class for logging operations.
```java
import java.text.SimpleDateFormat;
import java.util.Date;

public class Logger {
    private LogLevel level;
    private LogDestination destination;

    public Logger(LogLevel level, LogDestination destination) {
        this.level = level;
        this.destination = destination;
    }

    public void log(LogLevel level, String message) {
        if (level.ordinal() >= this.level.ordinal()) {
            String timestamp = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
            String formattedMessage = timestamp + " [" + level.name() + "] " + message;
            destination.writeLog(formattedMessage);
        }
    }

    // Getters and setters...
}
```