package lrucache

import (
	"sync"
)

// Node represents a node in the doubly linked list
type Node[K comparable, V any] struct {
	key   K
	value V
	prev  *Node[K, V]
	next  *Node[K, V]
}

// LRUCache represents a thread-safe LRU cache implementation
type LRUCache[K comparable, V any] struct {
	capacity int
	cache    map[K]*Node[K, V]
	head     *Node[K, V]
	tail     *Node[K, V]
	mu       sync.RWMutex
}

// NewLRUCache creates a new LRU cache with the specified capacity
func NewLRUCache[K comparable, V any](capacity int) *LRUCache[K, V] {
	cache := &LRUCache[K, V]{
		capacity: capacity,
		cache:    make(map[K]*Node[K, V]),
	}
	// Initialize dummy head and tail nodes
	cache.head = &Node[K, V]{}
	cache.tail = &Node[K, V]{}
	cache.head.next = cache.tail
	cache.tail.prev = cache.head
	return cache
}

// Get retrieves a value from the cache
func (c *LRUCache[K, V]) Get(key K) (V, bool) {
	c.mu.Lock()
	defer c.mu.Unlock()

	if node, exists := c.cache[key]; exists {
		c.moveToHead(node)
		return node.value, true
	}

	var zero V
	return zero, false
}

// Put adds or updates a value in the cache
func (c *LRUCache[K, V]) Put(key K, value V) {
	c.mu.Lock()
	defer c.mu.Unlock()

	if node, exists := c.cache[key]; exists {
		node.value = value
		c.moveToHead(node)
		return
	}

	newNode := &Node[K, V]{
		key:   key,
		value: value,
	}
	c.cache[key] = newNode
	c.addToHead(newNode)

	if len(c.cache) > c.capacity {
		lastNode := c.removeTail()
		delete(c.cache, lastNode.key)
	}
}

// addToHead adds a node right after the head
func (c *LRUCache[K, V]) addToHead(node *Node[K, V]) {
	node.prev = c.head
	node.next = c.head.next
	c.head.next.prev = node
	c.head.next = node
}

// removeNode removes a node from the list
func (c *LRUCache[K, V]) removeNode(node *Node[K, V]) {
	node.prev.next = node.next
	node.next.prev = node.prev
}

// moveToHead moves an existing node to the front of the list
func (c *LRUCache[K, V]) moveToHead(node *Node[K, V]) {
	c.removeNode(node)
	c.addToHead(node)
}

// removeTail removes and returns the last node before the tail
func (c *LRUCache[K, V]) removeTail() *Node[K, V] {
	node := c.tail.prev
	c.removeNode(node)
	return node
}

// Size returns the current number of items in the cache
func (c *LRUCache[K, V]) Size() int {
	c.mu.RLock()
	defer c.mu.RUnlock()
	return len(c.cache)
}

// Clear removes all items from the cache
func (c *LRUCache[K, V]) Clear() {
	c.mu.Lock()
	defer c.mu.Unlock()

	c.cache = make(map[K]*Node[K, V])
	c.head.next = c.tail
	c.tail.prev = c.head
}
