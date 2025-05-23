namespace Singleton
{
    public class LazySingleton
    {
        private static LazySingleton instance;
        private LazySingleton() { }
        public static LazySingleton GetInstance()
        {
            if (instance == null)
            {
                instance = new LazySingleton();
            }
            return instance;
        }
    }
} 