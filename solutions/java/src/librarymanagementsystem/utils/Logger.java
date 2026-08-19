package librarymanagementsystem.utils;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

/**
 * Simple logging utility.
 * Follows SRP - Only handles logging
 * In production, use a proper logging framework like Log4j or SLF4J
 */
public class Logger {
    private static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
    
    public enum LogLevel {
        INFO, WARNING, ERROR, DEBUG
    }
    
    /**
     * Log an info message.
     */
    public static void info(String message) {
        log(LogLevel.INFO, message);
    }
    
    /**
     * Log a warning message.
     */
    public static void warning(String message) {
        log(LogLevel.WARNING, message);
    }
    
    /**
     * Log an error message.
     */
    public static void error(String message) {
        log(LogLevel.ERROR, message);
    }
    
    /**
     * Log an error with exception.
     */
    public static void error(String message, Exception e) {
        log(LogLevel.ERROR, message + " - " + e.getMessage());
        e.printStackTrace();
    }
    
    /**
     * Log a debug message.
     */
    public static void debug(String message) {
        log(LogLevel.DEBUG, message);
    }
    
    /**
     * Core logging method.
     */
    private static void log(LogLevel level, String message) {
        String timestamp = LocalDateTime.now().format(formatter);
        String logMessage = String.format("[%s] [%s] %s", timestamp, level, message);
        
        switch (level) {
            case ERROR:
                System.err.println(logMessage);
                break;
            default:
                System.out.println(logMessage);
                break;
        }
    }
}