package lrucache

import (
	"fmt"
)

func Run() {
	// Create a new cache with capacity 3
	lruCache := NewLRUCache[int, string](3)

	// Add some values
	lruCache.Put(1, "Value 1")
	lruCache.Put(2, "Value 2")
	lruCache.Put(3, "Value 3")

	// Get values and print them
	if val, exists := lruCache.Get(1); exists {
		fmt.Println(val) // Output: Value 1
	}
	if val, exists := lruCache.Get(2); exists {
		fmt.Println(val) // Output: Value 2
	}

	// Add a new value that should evict the least recently used one
	lruCache.Put(4, "Value 4")

	// Try to get the evicted value
	if val, exists := lruCache.Get(3); exists {
		fmt.Println(val)
	} else {
		fmt.Println("Value 3 was evicted") // Output: Value 3 was evicted
	}

	// Get the newly added value
	if val, exists := lruCache.Get(4); exists {
		fmt.Println(val) // Output: Value 4
	}

	// Update an existing value
	lruCache.Put(2, "Updated Value 2")

	// Get the values again
	if val, exists := lruCache.Get(1); exists {
		fmt.Println(val) // Output: Value 1
	}
	if val, exists := lruCache.Get(2); exists {
		fmt.Println(val) // Output: Updated Value 2
	}
}
