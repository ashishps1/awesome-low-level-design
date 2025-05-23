#include "thread_safe_singleton.h"

// Initialize the static instance pointer and mutex
std::unique_ptr<ThreadSafeSingleton> ThreadSafeSingleton::instance = nullptr;
std::mutex ThreadSafeSingleton::mutex;

ThreadSafeSingleton& ThreadSafeSingleton::getInstance() {
    // Lock the mutex for thread safety
    std::lock_guard<std::mutex> lock(mutex);
    
    // Check if instance is null
    if (!instance) {
        // If null, create a new instance
        instance = std::unique_ptr<ThreadSafeSingleton>(new ThreadSafeSingleton());
    }
    // Return the instance (either newly created or existing)
    return *instance;
} 