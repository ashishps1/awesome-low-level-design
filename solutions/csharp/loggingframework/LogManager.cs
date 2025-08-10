using System.Collections.Concurrent;

class LogManager
{
    private static volatile LogManager instance;
    private static readonly object lockObject = new object();
    private readonly ConcurrentDictionary<string, Logger> loggers = new ConcurrentDictionary<string, Logger>();
    private readonly Logger rootLogger;
    private readonly AsyncLogProcessor processor;

    private LogManager()
    {
        this.rootLogger = new Logger("root", null);
        this.loggers.TryAdd("root", rootLogger);
        this.processor = new AsyncLogProcessor();
    }

    public static LogManager GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                    instance = new LogManager();
            }
        }
        return instance;
    }

    public Logger GetLogger(string name)
    {
        return loggers.GetOrAdd(name, CreateLogger);
    }

    private Logger CreateLogger(string name)
    {
        if (name.Equals("root"))
        {
            return rootLogger;
        }
        int lastDot = name.LastIndexOf('.');
        string parentName = (lastDot == -1) ? "root" : name.Substring(0, lastDot);
        Logger parent = GetLogger(parentName);
        return new Logger(name, parent);
    }

    public Logger GetRootLogger()
    {
        return rootLogger;
    }

    public AsyncLogProcessor GetProcessor()
    {
        return processor;
    }

    public void Shutdown()
    {
        // Stop the processor first to ensure all logs are written
        processor.Stop();

        // Then, close all appenders
        var allAppenders = loggers.Values
            .SelectMany(logger => logger.GetAppenders())
            .Distinct()
            .ToList();

        foreach (var appender in allAppenders)
        {
            appender.Close();
        }

        Console.WriteLine("Logging framework shut down gracefully.");
    }
}