using System;
using System.IO;

namespace LoggingFramework
{
    public class FileAppender : LogAppender
    {
        private readonly string _filePath;

        public FileAppender(string filePath)
        {
            _filePath = filePath;
        }

        public void Append(LogMessage logMessage)
        {
            try
            {
                using (var writer = new StreamWriter(_filePath, true))
                {
                    writer.WriteLine(logMessage.ToString());
                }
            }
            catch (IOException ex)
            {
                Console.WriteLine("FileAppender error: " + ex.Message);
            }
        }
    }
}