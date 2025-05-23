#include "lazy_singleton.h"

// Initialize the static instance pointer
std::unique_ptr<LazySingleton> LazySingleton::instance = nullptr;

LazySingleton& LazySingleton::getInstance() {
    // Check if instance is null
    if (!instance) {
        // If null, create a new instance
        instance = std::unique_ptr<LazySingleton>(new LazySingleton());
    }
    // Return the instance (either newly created or existing)
    return *instance;
} 