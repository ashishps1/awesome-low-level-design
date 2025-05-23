#include "build_system.h"

bool BuildSystem::compileProject() {
    std::cout << "BuildSystem: Compiling project..." << std::endl;
    simulateDelay(2000);
    std::cout << "BuildSystem: Build successful." << std::endl;
    return true;
}

std::string BuildSystem::getArtifactPath() {
    std::string path = "target/myapplication-1.0.jar";
    std::cout << "BuildSystem: Artifact located at " << path << std::endl;
    return path;
}

void BuildSystem::simulateDelay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
} 