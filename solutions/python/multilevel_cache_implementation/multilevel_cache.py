"""
Multilevel Cache System Implementation
Tiers: In-Memory -> SSD -> HDD
Uses LRU (Least Recently Used) eviction policy with cascading evictions.

Design Patterns Used:
- Chain of Responsibility: Each cache tier delegates to the next tier
- Strategy Pattern: LRU eviction strategy can be swapped
- Template Method: Common cache operations with tier-specific behavior
"""

from collections import OrderedDict
from abc import ABC, abstractmethod
from typing import Any, Optional, Tuple


class CacheTier(ABC):
    """Abstract base class for cache tiers (Template Method Pattern)"""
    
    def __init__(self, capacity: int, name: str, next_tier: Optional['CacheTier'] = None):
        self.capacity = capacity
        self.name = name
        self.next_tier = next_tier
        self.cache: OrderedDict[str, Any] = OrderedDict()
    
    def get(self, key: str) -> Tuple[Optional[Any], bool]:
        """
        Get value from cache. Returns (value, found).
        If found, moves key to end (most recently used).
        """
        if key in self.cache:
            # Move to end (most recently used)
            self.cache.move_to_end(key)
            print(f"  [HIT] Found '{key}' in {self.name}")
            return self.cache[key], True
        
        # Check next tier if exists
        if self.next_tier:
            value, found = self.next_tier.get(key)
            if found:
                # Promote to this tier (move up the hierarchy)
                self._put_with_eviction(key, value)
                return value, True
        
        return None, False
    
    def put(self, key: str, value: Any) -> None:
        """Put value into cache with LRU eviction if needed."""
        self._put_with_eviction(key, value)
    
    def _put_with_eviction(self, key: str, value: Any) -> None:
        """Internal put with eviction handling."""
        # If key exists, update and move to end
        if key in self.cache:
            self.cache[key] = value
            self.cache.move_to_end(key)
            print(f"  [UPDATE] Updated '{key}' in {self.name}")
            return
        
        # If at capacity, evict LRU item
        if len(self.cache) >= self.capacity:
            self._evict_lru()
        
        # Add new item
        self.cache[key] = value
        print(f"  [ADD] Added '{key}' to {self.name}")
    
    def _evict_lru(self) -> None:
        """Evict least recently used item and cascade to next tier."""
        if not self.cache:
            return
        
        # Pop LRU item (first item in OrderedDict)
        lru_key, lru_value = self.cache.popitem(last=False)
        print(f"  [EVICT] Evicted '{lru_key}' from {self.name}")
        
        # Cascade to next tier if exists
        if self.next_tier:
            print(f"  [CASCADE] Moving '{lru_key}' to {self.next_tier.name}")
            self.next_tier.put(lru_key, lru_value)
        else:
            print(f"  [DROP] '{lru_key}' dropped (no more tiers)")
    
    def delete(self, key: str) -> bool:
        """Delete key from all tiers."""
        deleted = False
        if key in self.cache:
            del self.cache[key]
            print(f"  [DELETE] Removed '{key}' from {self.name}")
            deleted = True
        
        if self.next_tier:
            deleted = self.next_tier.delete(key) or deleted
        
        return deleted
    
    def display(self) -> None:
        """Display cache contents."""
        items = list(self.cache.items())
        print(f"  {self.name} ({len(items)}/{self.capacity}): {items}")
        if self.next_tier:
            self.next_tier.display()
    
    @abstractmethod
    def get_access_time(self) -> float:
        """Simulated access time in milliseconds."""
        pass
    

class InMemoryCache(CacheTier):
    """Fastest tier - In-Memory Cache (RAM)"""
    
    def __init__(self, capacity: int, next_tier: Optional[CacheTier] = None):
        super().__init__(capacity, "InMemory (RAM)", next_tier)
    
    def get_access_time(self) -> float:
        return 0.1  # ~0.1ms


class SSDCache(CacheTier):
    """Medium tier - SSD Cache"""
    
    def __init__(self, capacity: int, next_tier: Optional[CacheTier] = None):
        super().__init__(capacity, "SSD", next_tier)
    
    def get_access_time(self) -> float:
        return 0.5  # ~0.5ms


class HDDCache(CacheTier):
    """Slowest tier - HDD Cache"""
    
    def __init__(self, capacity: int, next_tier: Optional[CacheTier] = None):
        super().__init__(capacity, "HDD", next_tier)
    
    def get_access_time(self) -> float:
        return 10.0  # ~10ms


class MultilevelCache:
    """
    Multilevel Cache System
    Chain of Responsibility: InMemory -> SSD -> HDD
    """
    
    def __init__(self, memory_capacity: int = 3, ssd_capacity: int = 5, hdd_capacity: int = 10):
        # Build the chain from bottom to top
        self.hdd = HDDCache(hdd_capacity)
        self.ssd = SSDCache(ssd_capacity, self.hdd)
        self.memory = InMemoryCache(memory_capacity, self.ssd)
        
        # Top tier is the entry point
        self.top_tier = self.memory
        
        print(f"Multilevel Cache initialized:")
        print(f"  - InMemory: {memory_capacity} slots")
        print(f"  - SSD: {ssd_capacity} slots")
        print(f"  - HDD: {hdd_capacity} slots")
        print()
    
    def get(self, key: str) -> Optional[Any]:
        """Get value from cache hierarchy."""
        print(f"GET '{key}':")
        value, found = self.top_tier.get(key)
        if not found:
            print(f"  [MISS] '{key}' not found in any tier")
        return value
    
    def put(self, key: str, value: Any) -> None:
        """Put value into top tier of cache."""
        print(f"PUT '{key}': {value}")
        self.top_tier.put(key, value)
    
    def delete(self, key: str) -> bool:
        """Delete key from all tiers."""
        print(f"DELETE '{key}':")
        return self.top_tier.delete(key)
    
    def display(self) -> None:
        """Display all cache tiers."""
        print("\n=== Cache State ===")
        self.top_tier.display()
        print("==================\n")


# Demo and Testing
if __name__ == "__main__":
    # Create cache with small capacities for demonstration
    # InMemory: 3, SSD: 5, HDD: 7
    cache = MultilevelCache(memory_capacity=3, ssd_capacity=5, hdd_capacity=7)
    
    print("=" * 50)
    print("DEMO: Multilevel Cache with LRU Eviction")
    print("=" * 50)
    
    # Add items to fill InMemory cache
    print("\n--- Adding items A, B, C (fills InMemory) ---")
    cache.put("A", "Value_A")
    cache.put("B", "Value_B")
    cache.put("C", "Value_C")
    cache.display()
    
    # Add more items - triggers eviction cascade
    print("\n--- Adding D (evicts A to SSD) ---")
    cache.put("D", "Value_D")
    cache.display()
    
    print("\n--- Adding E, F (more evictions) ---")
    cache.put("E", "Value_E")
    cache.put("F", "Value_F")
    cache.display()
    
    # Access an item from lower tier (promotes it)
    print("\n--- Accessing A (promotes from SSD to InMemory) ---")
    result = cache.get("A")
    print(f"Result: {result}")
    cache.display()
    
    # Access item in memory (just moves to MRU position)
    print("\n--- Accessing D (already in InMemory) ---")
    result = cache.get("D")
    print(f"Result: {result}")
    cache.display()
    
    # Add more items to demonstrate full cascade
    print("\n--- Adding G, H, I, J, K (cascade through all tiers) ---")
    for key in ["G", "H", "I", "J", "K"]:
        cache.put(key, f"Value_{key}")
    cache.display()
    
    # Try to get an item that doesn't exist
    print("\n--- Accessing non-existent key 'Z' ---")
    result = cache.get("Z")
    print(f"Result: {result}")
    
    # Delete an item
    print("\n--- Deleting 'B' ---")
    cache.delete("B")
    cache.display()
    
    print("\n" + "=" * 50)
    print("DEMO COMPLETE")
    print("=" * 50)
