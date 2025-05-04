# LRU Cache (LLD)

## Problem Statement

Design and implement an LRU (Least Recently Used) Cache with a fixed capacity. The cache should support fast retrieval and insertion, and automatically evict the least recently used item when the capacity is exceeded.

---

## Requirements

- **Fixed Capacity:** The cache has a maximum size. When full, the least recently used item is evicted on insertion.
- **Fast Operations:** Both `get(key)` and `put(key, value)` operations should be O(1).
- **Eviction Policy:** The least recently used item is removed when the cache exceeds its capacity.
- **Extensibility:** Easy to change the eviction policy or underlying data structures.

---

## Core Entities

- **LRUCache:** Main class implementing the cache logic, manages storage and eviction.
- **Node:** Represents a doubly-linked list node for fast removal and insertion.

---

## Class Design

### 1. LRUCache
- **Fields:** capacity, Map<K, Node<K, V>>, head/tail pointers for the doubly-linked list
- **Methods:**
  - `get(K key)`: Returns the value for the key if present, else -1/null. Moves the node to the front (most recently used).
  - `put(K key, V value)`: Inserts or updates the value for the key. Moves the node to the front. If the cache exceeds capacity, evicts the least recently used node.
  - `removeNode(Node)`, `addToFront(Node)`, `moveToFront(Node)`, `evictLRU()`: Helper methods for list management.

### 2. Node
- **Fields:** key, value, prev, next

---

## Design Patterns Used

- **Doubly Linked List:** For O(1) removal and insertion of nodes.
- **Hash Map:** For O(1) access to nodes by key.
- **Separation of Concerns:** Node and cache logic are separated.

---

## Example Usage

```java
LRUCache cache = new LRUCache(2);
cache.put(1, 1); // cache: {1=1}
cache.put(2, 2); // cache: {1=1, 2=2}
cache.get(1);    // returns 1, cache: {2=2, 1=1}
cache.put(3, 3); // evicts key 2, cache: {1=1, 3=3}
cache.get(2);    // returns -1 (not found)
```

---

## Demo

See `LRUCacheDemo.java` for a sample usage and simulation of the LRU cache.

---

## Extending the Framework

- **Change eviction policy:** Implement a different policy (e.g., LFU) by modifying the eviction logic.
- **Change data structures:** Use other structures for different performance characteristics.

---