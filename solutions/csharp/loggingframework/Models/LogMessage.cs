class LogMessage
{
    private readonly DateTime timestamp;
    private readonly LogLevel level;
    private readonly string loggerName;
    private readonly string threadName;
    private readonly string message;

    public LogMessage(LogLevel level, string loggerName, string message)
    {
        this.timestamp = DateTime.Now;
        this.level = level;
        this.loggerName = loggerName;
        this.message = message;
        this.threadName = Thread.CurrentThread.Name ?? Thread.CurrentThread.ManagedThreadId.ToString();
    }

    public DateTime GetTimestamp() { return timestamp; }
    public LogLevel GetLevel() { return level; }
    public string GetLoggerName() { return loggerName; }
    public string GetThreadName() { return threadName; }
    public string GetMessage() { return message; }
}