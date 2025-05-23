#include "eager_singleton.h"
#include "lazy_singleton.h"
#include "thread_safe_singleton.h"
#include "double_checked_singleton.h"
#include <iostream>

int main() {
    std::cout << "=== Singleton Pattern Demo ===\n" << std::endl;

    // Test EagerSingleton
    std::cout << "Testing EagerSingleton:" << std::endl;
    EagerSingleton& eager1 = EagerSingleton::getInstance();
    EagerSingleton& eager2 = EagerSingleton::getInstance();
    std::cout << "EagerSingleton instances are the same: " 
              << (&eager1 == &eager2) << std::endl;

    // Test LazySingleton
    std::cout << "\nTesting LazySingleton:" << std::endl;
    LazySingleton& lazy1 = LazySingleton::getInstance();
    LazySingleton& lazy2 = LazySingleton::getInstance();
    std::cout << "LazySingleton instances are the same: " 
              << (&lazy1 == &lazy2) << std::endl;

    // Test ThreadSafeSingleton
    std::cout << "\nTesting ThreadSafeSingleton:" << std::endl;
    ThreadSafeSingleton& threadSafe1 = ThreadSafeSingleton::getInstance();
    ThreadSafeSingleton& threadSafe2 = ThreadSafeSingleton::getInstance();
    std::cout << "ThreadSafeSingleton instances are the same: " 
              << (&threadSafe1 == &threadSafe2) << std::endl;

    // Test DoubleCheckedSingleton
    std::cout << "\nTesting DoubleCheckedSingleton:" << std::endl;
    DoubleCheckedSingleton& doubleChecked1 = DoubleCheckedSingleton::getInstance();
    DoubleCheckedSingleton& doubleChecked2 = DoubleCheckedSingleton::getInstance();
    std::cout << "DoubleCheckedSingleton instances are the same: " 
              << (&doubleChecked1 == &doubleChecked2) << std::endl;

    return 0;
} 