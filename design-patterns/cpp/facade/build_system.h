#pragma once
#include <string>
#include <chrono>
#include <thread>
#include <iostream>

class BuildSystem {
public:
    bool compileProject();
    std::string getArtifactPath();
private:
    void simulateDelay(int ms);
}; 