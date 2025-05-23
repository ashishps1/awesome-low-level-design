#pragma once
#include <chrono>
#include <thread>
#include <iostream>

class TestingFramework {
public:
    bool runUnitTests();
    bool runIntegrationTests();
private:
    void simulateDelay(int ms);
}; 