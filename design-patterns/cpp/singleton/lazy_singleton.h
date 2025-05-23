#pragma once
#include <memory>

class LazySingleton {
public:
    // Delete copy constructor and assignment operator
    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;

    // Public method to get the instance
    static LazySingleton& getInstance();

private:
    // Private constructor to prevent instantiation
    LazySingleton() = default;
    
    // The single instance, initially null
    static std::unique_ptr<LazySingleton> instance;
}; 