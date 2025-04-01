using System;

namespace LoggingFramework
{
    public class Logger
    {
        private static readonly Logger _instance = new Logger();
        private LoggerConfig _config;

        private Logger()
        {
            // Private constructor to enforce singleton pattern
            _config = new LoggerConfig(LogLevel.INFO, new ConsoleAppender());
        }

        public static Logger GetInstance()
        {
            return _instance;
        }

        public void SetConfig(LoggerConfig config)
        {
            _config = config;
        }

        public void Log(LogLevel level, string message)
        {
            if (level >= _config.LogLevel)
            {
                LogMessage logMessage = new LogMessage(level, message);
                _config.LogAppender.Append(logMessage);
            }
        }

        public void Debug(string message)
        {
            Log(LogLevel.DEBUG, message);
        }

        public void Info(string message)
        {
            Log(LogLevel.INFO, message);
        }

        public void Warning(string message)
        {
            Log(LogLevel.WARNING, message);
        }

        public void Error(string message)
        {
            Log(LogLevel.ERROR, message);
        }

        public void Fatal(string message)
        {
            Log(LogLevel.FATAL, message);
        }
    }
}