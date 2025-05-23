namespace Singleton
{
    public class DoubleCheckedLockingSingleton
    {
        private static volatile DoubleCheckedLockingSingleton instance;
        private static readonly object lockObj = new object();
        private DoubleCheckedLockingSingleton() { }
        public static DoubleCheckedLockingSingleton GetInstance()
        {
            if (instance == null)
            {
                lock (lockObj)
                {
                    if (instance == null)
                    {
                        instance = new DoubleCheckedLockingSingleton();
                    }
                }
            }
            return instance;
        }
    }
} 