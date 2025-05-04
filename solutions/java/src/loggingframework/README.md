# Logging Framework (LLD)

## Problem Statement

Design and implement a flexible and extensible logging framework that can be used by applications to log messages at different levels (INFO, DEBUG, ERROR, etc.), support multiple output destinations (console, file, etc.), and allow for custom formatting of log messages.

---

## Requirements

- **Log Levels:** Support for multiple log levels (INFO, DEBUG, ERROR, etc.).
- **Multiple Appenders:** Ability to log to different destinations (console, file, etc.).
- **Custom Formatting:** Support for custom log message formatting.
- **Configuration:** Ability to configure loggers and appenders.
- **Thread Safety:** Should be thread-safe for concurrent logging.
- **Extensibility:** Easy to add new log levels, appenders, or formatters.

---

## Core Entities

- **Logger:** Main class used by clients to log messages.
- **LogLevel:** Enum representing different log levels.
- **LogMessage:** Encapsulates the details of a log event.
- **LogFormatter:** Interface for formatting log messages.
- **DefaultFormatter:** Default implementation of `LogFormatter`.
- **LoggerConfig:** Holds configuration for the logger (appenders, formatters, etc.).
- **LogAppender (in `logappender/`):** Interface and implementations for output destinations (e.g., ConsoleAppender, FileAppender).

---

## Class Design

### 1. Logger
- **Methods:**
  - `log(LogLevel level, String message)`
  - `info(String message)`
  - `debug(String message)`
  - `error(String message)`
  - `setConfig(LoggerConfig config)`

### 2. LogLevel
- Enum for log levels (INFO, DEBUG, ERROR, etc.)

### 3. LogMessage
- Fields: `level`, `message`, `timestamp`, etc.

### 4. LogFormatter (Interface)
- `String format(LogMessage message)`

### 5. DefaultFormatter
- Implements `LogFormatter` with a default format.

### 6. LoggerConfig
- Holds configuration for loggers (appenders, formatters, log level).

### 7. LogAppender (in `logappender/`)
- Interface for appenders.
- Implementations: `ConsoleAppender`, `FileAppender`, etc.

---

## Design Patterns Used

- **Strategy Pattern:** For interchangeable log formatters and appenders.
- **Singleton Pattern:** (If used) For global logger instance.
- **Factory Pattern:** (Optional) For creating appenders/formatters based on config.
- **Observer Pattern:** (Conceptually, for notifying multiple appenders.)

---

## Example Usage

```java
Logger logger = new Logger();
logger.setConfig(new LoggerConfig(...));
logger.info("Application started");
logger.error("An error occurred");
```

---

## Demo

See `LoggingFrameworkDemo.java` for a sample usage of the logging framework.

---

## Extending the Framework

- **Add a new log level:** Update `LogLevel.java`.
- **Add a new appender:** Implement the `LogAppender` interface in `logappender/`.
- **Add a new formatter:** Implement the `LogFormatter` interface.

---