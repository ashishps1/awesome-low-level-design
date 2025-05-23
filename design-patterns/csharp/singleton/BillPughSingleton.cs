namespace Singleton
{
    public class BillPughSingleton
    {
        private BillPughSingleton() { }
        public static BillPughSingleton GetInstance()
        {
            return Nested.instance;
        }
        private class Nested
        {
            internal static readonly BillPughSingleton instance = new BillPughSingleton();
            static Nested() { }
        }
    }
} 