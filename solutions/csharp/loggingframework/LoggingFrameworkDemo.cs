namespace LoggingFramework
{
    public class LoggingFrameworkDemo
    {
        public static void Run()
        {
            Logger logger = Logger.GetInstance();

            // Logging with default configuration
            logger.Info("This is an information message");
            logger.Warning("This is a warning message");
            logger.Error("This is an error message");

            // Changing log level and appender
            LoggerConfig config = new LoggerConfig(LogLevel.DEBUG, new FileAppender("app.log"));
            logger.SetConfig(config);

            logger.Debug("This is a debug message");
            logger.Info("This is an information message");
        }
    }
}