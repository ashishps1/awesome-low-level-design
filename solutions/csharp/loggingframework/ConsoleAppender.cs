using System;

namespace LoggingFramework
{
    public class ConsoleAppender : LogAppender
    {
        public void Append(LogMessage logMessage)
        {
            Console.WriteLine(logMessage.ToString());
        }
    }
}