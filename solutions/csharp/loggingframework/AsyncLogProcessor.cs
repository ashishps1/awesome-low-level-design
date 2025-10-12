using System.Collections.Concurrent;

class AsyncLogProcessor
{
    private readonly ConcurrentQueue<Action> taskQueue = new ConcurrentQueue<Action>();
    private readonly AutoResetEvent signal = new AutoResetEvent(false);
    private volatile bool shutdownFlag = false;
    private readonly Thread workerThread;

    public AsyncLogProcessor()
    {
        workerThread = new Thread(WorkerLoop)
        {
            Name = "AsyncLogProcessor",
            IsBackground = true
        };
        workerThread.Start();
    }

    private void WorkerLoop()
    {
        while (!shutdownFlag)
        {
            signal.WaitOne();
            
            while (taskQueue.TryDequeue(out Action task))
            {
                try
                {
                    task();
                }
                catch (Exception e)
                {
                    Console.WriteLine($"Error processing log task: {e.Message}");
                }
            }
        }
    }

    public void Process(LogMessage logMessage, List<ILogAppender> appenders)
    {
        if (shutdownFlag)
        {
            Console.Error.WriteLine("Logger is shut down. Cannot process log message.");
            return;
        }

        taskQueue.Enqueue(() =>
        {
            foreach (var appender in appenders)
            {
                appender.Append(logMessage);
            }
        });
        signal.Set();
    }

    public void Stop()
    {
        shutdownFlag = true;
        signal.Set();
        
        if (!workerThread.Join(TimeSpan.FromSeconds(2)))
        {
            Console.Error.WriteLine("Logger executor did not terminate in the specified time.");
            workerThread.Abort();
        }
    }
}