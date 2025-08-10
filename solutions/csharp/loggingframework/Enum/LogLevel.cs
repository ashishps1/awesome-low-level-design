enum LogLevel
{
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
}

static class LogLevelExtensions
{
    public static bool IsGreaterOrEqual(this LogLevel level, LogLevel other)
    {
        return (int)level >= (int)other;
    }
}