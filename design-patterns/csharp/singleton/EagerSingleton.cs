namespace Singleton
{
    public class EagerSingleton
    {
        private static readonly EagerSingleton instance = new EagerSingleton();
        private EagerSingleton() { }
        public static EagerSingleton GetInstance()
        {
            return instance;
        }
    }
} 