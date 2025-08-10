class Logger
{
    private readonly string name;
    private LogLevel? level;
    private readonly Logger parent;
    private readonly List<ILogAppender> appenders;
    private bool additivity = true;

    public Logger(string name, Logger parent)
    {
        this.name = name;
        this.parent = parent;
        this.appenders = new List<ILogAppender>();
    }

    public void AddAppender(ILogAppender appender)
    {
        appenders.Add(appender);
    }

    public List<ILogAppender> GetAppenders()
    {
        return new List<ILogAppender>(appenders);
    }

    public void SetLevel(LogLevel minLevel)
    {
        this.level = minLevel;
    }

    public void SetAdditivity(bool additivity)
    {
        this.additivity = additivity;
    }

    public LogLevel GetEffectiveLevel()
    {
        for (Logger logger = this; logger != null; logger = logger.parent)
        {
            LogLevel? currentLevel = logger.level;
            if (currentLevel.HasValue)
            {
                return currentLevel.Value;
            }
        }
        return LogLevel.DEBUG; // Default root level
    }

    public void Log(LogLevel messageLevel, string message)
    {
        if (messageLevel.IsGreaterOrEqual(GetEffectiveLevel()))
        {
            LogMessage logMessage = new LogMessage(messageLevel, this.name, message);
            CallAppenders(logMessage);
        }
    }

    private void CallAppenders(LogMessage logMessage)
    {
        if (appenders.Count > 0)
        {
            LogManager.GetInstance().GetProcessor().Process(logMessage, this.appenders);
        }
        if (additivity && parent != null)
        {
            parent.CallAppenders(logMessage);
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

    public void Warn(string message)
    {
        Log(LogLevel.WARN, message);
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