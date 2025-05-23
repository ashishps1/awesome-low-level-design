namespace Singleton
{
    public class ThreadSafeSingleton
    {
        private static ThreadSafeSingleton instance;
        private static readonly object lockObj = new object();
        private ThreadSafeSingleton() { }
        public static ThreadSafeSingleton GetInstance()
        {
            lock (lockObj)
            {
                if (instance == null)
                {
                    instance = new ThreadSafeSingleton();
                }
                return instance;
            }
        }
    }
} 