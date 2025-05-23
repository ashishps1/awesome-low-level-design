#pragma once
#include <memory>
#include <mutex>

class ThreadSafeSingleton {
public:
    // Delete copy constructor and assignment operator
    ThreadSafeSingleton(const ThreadSafeSingleton&) = delete;
    ThreadSafeSingleton& operator=(const ThreadSafeSingleton&) = delete;

    // Public method to get the instance
    static ThreadSafeSingleton& getInstance();

private:
    // Private constructor to prevent instantiation
    ThreadSafeSingleton() = default;
    
    // The single instance, initially null
    static std::unique_ptr<ThreadSafeSingleton> instance;
    
    // Mutex for thread safety
    static std::mutex mutex;
}; 