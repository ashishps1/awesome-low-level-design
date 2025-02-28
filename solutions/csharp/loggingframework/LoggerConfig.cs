namespace LoggingFramework
{
    public class LoggerConfig
    {
        public LogLevel LogLevel { get; set; }
        public LogAppender LogAppender { get; set; }

        public LoggerConfig(LogLevel logLevel, LogAppender logAppender)
        {
            LogLevel = logLevel;
            LogAppender = logAppender;
        }
    }
}