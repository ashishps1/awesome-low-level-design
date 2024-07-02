from lru_cache import LRUCache

class LRUCacheDemo:
    @staticmethod
    def run():
        cache = LRUCache(3)

        cache.put(1, "Value 1")
        cache.put(2, "Value 2")
        cache.put(3, "Value 3")

        print(cache.get(1))  # Output: Value 1
        print(cache.get(2))  # Output: Value 2

        cache.put(4, "Value 4")

        print(cache.get(3))  # Output: None
        print(cache.get(4))  # Output: Value 4

        cache.put(2, "Updated Value 2")

        print(cache.get(1))  # Output: Value 1
        print(cache.get(2))  # Output: Updated Value 2

if __name__ == "__main__":
    LRUCacheDemo.run()