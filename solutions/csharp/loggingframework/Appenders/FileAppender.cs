class FileAppender : ILogAppender
{
    private StreamWriter writer;
    private ILogFormatter formatter;
    private readonly object fileLock = new object();

    public FileAppender(string filePath)
    {
        this.formatter = new SimpleTextFormatter();
        try
        {
            this.writer = new StreamWriter(filePath, true);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Failed to create writer for file logs, exception: {e.Message}");
            this.writer = null;
        }
    }

    public void Append(LogMessage logMessage)
    {
        lock (fileLock)
        {
            if (writer != null)
            {
                try
                {
                    writer.Write(formatter.Format(logMessage) + "\n");
                    writer.Flush();
                }
                catch (Exception e)
                {
                    Console.WriteLine($"Failed to write logs to file, exception: {e.Message}");
                }
            }
        }
    }

    public void Close()
    {
        if (writer != null)
        {
            try
            {
                writer.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine($"Failed to close logs file, exception: {e.Message}");
            }
        }
    }

    public void SetFormatter(ILogFormatter formatter)
    {
        this.formatter = formatter;
    }

    public ILogFormatter GetFormatter()
    {
        return formatter;
    }
}