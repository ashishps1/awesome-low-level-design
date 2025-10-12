package loggingframework;

import loggingframework.enums.LogLevel;
import loggingframework.strategies.appender.ConsoleAppender;

public class LoggingFrameworkDemo {
    public static void main(String[] args) {
        // --- 1. Initial Configuration ---
        LogManager logManager = LogManager.getInstance();
        Logger rootLogger = logManager.getRootLogger();
        rootLogger.setLevel(LogLevel.INFO); // Set global minimum level to INFO

        // Add a console appender to the root logger
        rootLogger.addAppender(new ConsoleAppender());

        System.out.println("--- Initial Logging Demo ---");
        Logger mainLogger = logManager.getLogger("com.example.Main");
        mainLogger.info("Application starting up.");
        mainLogger.debug("This is a debug message, it should NOT appear."); // Below root level
        mainLogger.warn("This is a warning message.");

        // --- 2. Hierarchy and Additivity Demo ---
        System.out.println("\n--- Logger Hierarchy Demo ---");
        Logger dbLogger = logManager.getLogger("com.example.db");
        // dbLogger inherits level and appenders from root
        dbLogger.info("Database connection pool initializing.");

        // Let's create a more specific logger and override its level
        Logger serviceLogger = logManager.getLogger("com.example.service.UserService");
        serviceLogger.setLevel(LogLevel.DEBUG); // More verbose logging for this specific service
        serviceLogger.info("User service starting.");
        serviceLogger.debug("This debug message SHOULD now appear for the service logger.");

        // --- 3. Dynamic Configuration Change ---
        System.out.println("\n--- Dynamic Configuration Demo ---");
        System.out.println("Changing root log level to DEBUG...");
        rootLogger.setLevel(LogLevel.DEBUG);
        mainLogger.debug("This debug message should now be visible.");

        try {
            Thread.sleep(500);
            logManager.shutdown();
        } catch (Exception e) {
            System.out.println("Caught exception");
        }
    }
}