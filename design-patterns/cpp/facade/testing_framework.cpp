#include "testing_framework.h"

bool TestingFramework::runUnitTests() {
    std::cout << "Testing: Running unit tests..." << std::endl;
    simulateDelay(1500);
    std::cout << "Testing: Unit tests passed." << std::endl;
    return true;
}

bool TestingFramework::runIntegrationTests() {
    std::cout << "Testing: Running integration tests..." << std::endl;
    simulateDelay(3000);
    std::cout << "Testing: Integration tests passed." << std::endl;
    return true;
}

void TestingFramework::simulateDelay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
} 