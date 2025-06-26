package lrucache;

public class LRUCacheDemo {
    public static void run() {
        LRUCache<String, Integer> cache = new LRUCache<>(3);

        cache.put("a", 1);
        cache.put("b", 2);
        cache.put("c", 3);

        System.out.println(cache.get("a")); // 1

        cache.put("d", 4);
        
        System.out.println(cache.get("b")); // null
    }
}
