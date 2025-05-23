#pragma once

class EagerSingleton {
public:
    // Delete copy constructor and assignment operator
    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;

    // Public method to get the instance
    static EagerSingleton& getInstance();

private:
    // Private constructor to prevent instantiation
    EagerSingleton() = default;
    
    // The single instance, created immediately
    static EagerSingleton instance;
}; 