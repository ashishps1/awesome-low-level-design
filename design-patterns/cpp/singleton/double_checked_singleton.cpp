#include "double_checked_singleton.h"

// Initialize the static instance pointer and mutex
std::atomic<DoubleCheckedSingleton*> DoubleCheckedSingleton::instance = nullptr;
std::mutex DoubleCheckedSingleton::mutex;

DoubleCheckedSingleton& DoubleCheckedSingleton::getInstance() {
    // First check (not synchronized)
    DoubleCheckedSingleton* p = instance.load(std::memory_order_acquire);
    if (!p) {
        // Lock the mutex
        std::lock_guard<std::mutex> lock(mutex);
        
        // Second check (synchronized)
        p = instance.load(std::memory_order_relaxed);
        if (!p) {
            // Create the instance
            p = new DoubleCheckedSingleton();
            instance.store(p, std::memory_order_release);
        }
    }
    return *p;
} 