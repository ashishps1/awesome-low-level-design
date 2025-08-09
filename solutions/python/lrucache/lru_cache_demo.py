from lru_cache import LRUCache

class LRUCacheDemo:
    @staticmethod
    def main():
        cache: LRUCache[str, int] = LRUCache(3)

        cache.put("a", 1)
        cache.put("b", 2)
        cache.put("c", 3)

        # Accessing 'a' makes it the most recently used
        print(cache.get("a"))  # 1

        # Adding 'd' will cause 'b' (the current LRU item) to be evicted
        cache.put("d", 4)

        # Trying to get 'b' should now return None
        print(cache.get("b"))  # None

if __name__ == "__main__":
    LRUCacheDemo.main()