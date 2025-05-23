using System;

namespace Singleton
{
    public class StaticBlockSingleton
    {
        private static readonly StaticBlockSingleton instance;
        static StaticBlockSingleton()
        {
            try
            {
                instance = new StaticBlockSingleton();
            }
            catch (Exception ex)
            {
                throw new Exception("Exception occurred in creating singleton instance", ex);
            }
        }
        private StaticBlockSingleton() { }
        public static StaticBlockSingleton GetInstance()
        {
            return instance;
        }
    }
} 