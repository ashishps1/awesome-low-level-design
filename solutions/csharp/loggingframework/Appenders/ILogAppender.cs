interface ILogAppender
{
    void Append(LogMessage logMessage);
    void Close();
    ILogFormatter GetFormatter();
    void SetFormatter(ILogFormatter formatter);
}