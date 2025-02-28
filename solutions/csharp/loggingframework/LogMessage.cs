using System;

namespace LoggingFramework
{
    public class LogMessage
    {
        public LogLevel Level { get; }
        public string Message { get; }
        public long Timestamp { get; }

        public LogMessage(LogLevel level, string message)
        {
            Level = level;
            Message = message;
            Timestamp = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();
        }

        public override string ToString()
        {
            return $"[{Level}] {Timestamp} - {Message}";
        }
    }
}