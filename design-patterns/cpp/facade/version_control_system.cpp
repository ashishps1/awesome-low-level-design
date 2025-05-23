#include "version_control_system.h"

void VersionControlSystem::pullLatestChanges(const std::string& branch) {
    std::cout << "VCS: Pulling latest changes from '" << branch << "'..." << std::endl;
    simulateDelay();
    std::cout << "VCS: Pull complete." << std::endl;
}

void VersionControlSystem::simulateDelay() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
} 