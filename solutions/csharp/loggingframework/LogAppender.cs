namespace LoggingFramework
{
    public interface LogAppender
    {
        void Append(LogMessage logMessage);
    }
}