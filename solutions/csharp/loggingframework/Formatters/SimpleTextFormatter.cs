class SimpleTextFormatter : ILogFormatter
{
    public string Format(LogMessage logMessage)
    {
        return $"{logMessage.GetTimestamp():yyyy-MM-dd HH:mm:ss.fff} [{logMessage.GetThreadName()}] {logMessage.GetLevel()} - {logMessage.GetLoggerName()}: {logMessage.GetMessage()}\n";
    }
}