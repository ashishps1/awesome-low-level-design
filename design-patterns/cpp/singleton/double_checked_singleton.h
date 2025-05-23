#pragma once
#include <memory>
#include <mutex>
#include <atomic>

class DoubleCheckedSingleton {
public:
    // Delete copy constructor and assignment operator
    DoubleCheckedSingleton(const DoubleCheckedSingleton&) = delete;
    DoubleCheckedSingleton& operator=(const DoubleCheckedSingleton&) = delete;

    // Public method to get the instance
    static DoubleCheckedSingleton& getInstance();

private:
    // Private constructor to prevent instantiation
    DoubleCheckedSingleton() = default;
    
    // The single instance, initially null
    static std::atomic<DoubleCheckedSingleton*> instance;
    
    // Mutex for thread safety
    static std::mutex mutex;
}; 