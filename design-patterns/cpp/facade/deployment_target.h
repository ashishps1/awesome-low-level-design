#pragma once
#include <string>
#include <chrono>
#include <thread>
#include <iostream>

class DeploymentTarget {
public:
    void transferArtifact(const std::string& artifactPath, const std::string& server);
    void activateNewVersion(const std::string& server);
private:
    void simulateDelay(int ms);
}; 