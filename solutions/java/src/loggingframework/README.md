# Designing a Logging Framework

## Requirements
1. The logging framework should support different log levels, such as DEBUG, INFO, WARNING, ERROR, and FATAL.
2. It should allow logging messages with a timestamp, log level, and message content.
3. The framework should support multiple output destinations, such as console, file, and database.
4. It should provide a configuration mechanism to set the log level and output destination.
5. The logging framework should be thread-safe to handle concurrent logging from multiple threads.
6. It should be extensible to accommodate new log levels and output destinations in the future.

## Classes, Interfaces and Enumerations
1. The **LogLevel** enum defines the different log levels supported by the logging framework.
2. The **LogMessage** class represents a log message with a timestamp, log level, and message content.
3. The **LogAppender** interface defines the contract for appending log messages to different output destinations.
4. The **ConsoleAppender**, **FileAppender**, and **DatabaseAppender** classes are concrete implementations of the LogAppender interface, supporting logging to the console, file, and database, respectively.
5. The **LoggerConfig** class holds the configuration settings for the logger, including the log level and the selected log appender.
6. The **Logger** class is a singleton that provides the main logging functionality. It allows setting the configuration, logging messages at different levels, and provides convenience methods for each log level.
7. The **LoggingExample** class demonstrates the usage of the logging framework, showcasing different log levels, changing the configuration, and logging from multiple threads.