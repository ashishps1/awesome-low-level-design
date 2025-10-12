using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Linq;

public class LoggingFrameworkDemo
{
    public static void Main(string[] args)
    {
        // --- 1. Initial Configuration ---
        LogManager logManager = LogManager.GetInstance();
        Logger rootLogger = logManager.GetRootLogger();
        rootLogger.SetLevel(LogLevel.INFO); // Set global minimum level to INFO

        // Add a console appender to the root logger
        rootLogger.AddAppender(new ConsoleAppender());

        Console.WriteLine("--- Initial Logging Demo ---");
        Logger mainLogger = logManager.GetLogger("com.example.Main");
        mainLogger.Info("Application starting up.");
        mainLogger.Debug("This is a debug message, it should NOT appear."); // Below root level
        mainLogger.Warn("This is a warning message.");

        // --- 2. Hierarchy and Additivity Demo ---
        Console.WriteLine("\n--- Logger Hierarchy Demo ---");
        Logger dbLogger = logManager.GetLogger("com.example.db");
        // dbLogger inherits level and appenders from root
        dbLogger.Info("Database connection pool initializing.");

        // Let's create a more specific logger and override its level
        Logger serviceLogger = logManager.GetLogger("com.example.service.UserService");
        serviceLogger.SetLevel(LogLevel.DEBUG); // More verbose logging for this specific service
        serviceLogger.Info("User service starting.");
        serviceLogger.Debug("This debug message SHOULD now appear for the service logger.");

        // --- 3. Dynamic Configuration Change ---
        Console.WriteLine("\n--- Dynamic Configuration Demo ---");
        Console.WriteLine("Changing root log level to DEBUG...");
        rootLogger.SetLevel(LogLevel.DEBUG);
        mainLogger.Debug("This debug message should now be visible.");

        try
        {
            Thread.Sleep(500);
            logManager.Shutdown();
        }
        catch (Exception e)
        {
            Console.WriteLine("Caught exception");
        }
    }
}