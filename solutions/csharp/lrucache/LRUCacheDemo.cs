using System;

namespace LRUCacheNamespace
{
    public class LRUCacheDemo
    {
        public static void Run()
        {
            var cache = new LRUCache<int, string>(3);

            cache.Put(1, "Value 1");
            cache.Put(2, "Value 2");
            cache.Put(3, "Value 3");

            Console.WriteLine(cache.Get(1)); // Output: Value 1
            Console.WriteLine(cache.Get(2)); // Output: Value 2

            cache.Put(4, "Value 4");

            Console.WriteLine(cache.Get(3)); // Output: null (as it has been removed)
            Console.WriteLine(cache.Get(4)); // Output: Value 4

            cache.Put(2, "Updated Value 2");

            Console.WriteLine(cache.Get(1)); // Output: Value 1
            Console.WriteLine(cache.Get(2)); // Output: Updated Value 2
        }
    }
}