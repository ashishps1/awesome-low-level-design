#pragma once
#include <string>
#include <chrono>
#include <thread>
#include <iostream>

class VersionControlSystem {
public:
    void pullLatestChanges(const std::string& branch);
private:
    void simulateDelay();
}; 