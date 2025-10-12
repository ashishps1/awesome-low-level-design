using System;
using System.Collections.Generic;

public class LRUCacheDemo
{
    public static void Main()
    {
        LRUCache<string, int> cache = new LRUCache<string, int>(3);

        cache.Put("a", 1);
        cache.Put("b", 2);
        cache.Put("c", 3);

        Console.WriteLine(cache.Get("a")); // 1

        cache.Put("d", 4);

        Console.WriteLine(cache.Get("b")); // 0 (default for int when null)
    }
}