class ConsoleAppender : ILogAppender
{
    private ILogFormatter formatter;

    public ConsoleAppender()
    {
        this.formatter = new SimpleTextFormatter();
    }

    public void Append(LogMessage logMessage)
    {
        Console.Write(formatter.Format(logMessage));
    }

    public void Close() { }

    public void SetFormatter(ILogFormatter formatter)
    {
        this.formatter = formatter;
    }

    public ILogFormatter GetFormatter()
    {
        return formatter;
    }
}