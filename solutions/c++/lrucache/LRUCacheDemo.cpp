#include "LRUCache.hpp"
#include <iostream>
#include <string>

int main() {
    // Create LRU cache with capacity 3
    LRUCache<int, std::string> cache(3);
    
    // Add some entries
    std::cout << "Adding entries to cache..." << std::endl;
    cache.put(1, "One");
    cache.put(2, "Two");
    cache.put(3, "Three");
    cache.display();
    
    // Try to get an entry
    std::cout << "\nGetting value for key 2..." << std::endl;
    std::cout << "Value: " << cache.get(2) << std::endl;
    cache.display();  // 2 should move to front
    
    // Add new entry when cache is full
    std::cout << "\nAdding new entry when cache is full..." << std::endl;
    cache.put(4, "Four");  // Should evict least recently used item
    cache.display();
    
    // Try to access non-existent key
    std::cout << "\nTrying to access non-existent key..." << std::endl;
    try {
        cache.get(1);  // Should throw exception
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Update existing entry
    std::cout << "\nUpdating existing entry..." << std::endl;
    cache.put(2, "Two Updated");
    cache.display();
    
    // Clear cache
    std::cout << "\nClearing cache..." << std::endl;
    cache.clear();
    cache.display();
    
    return 0;
} 