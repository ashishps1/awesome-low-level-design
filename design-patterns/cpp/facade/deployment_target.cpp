#include "deployment_target.h"

void DeploymentTarget::transferArtifact(const std::string& artifactPath, const std::string& server) {
    std::cout << "Deployment: Transferring " << artifactPath << " to " << server << "..." << std::endl;
    simulateDelay(1000);
    std::cout << "Deployment: Transfer complete." << std::endl;
}

void DeploymentTarget::activateNewVersion(const std::string& server) {
    std::cout << "Deployment: Activating new version on " << server << "..." << std::endl;
    simulateDelay(500);
    std::cout << "Deployment: Now live on " << server << "!" << std::endl;
}

void DeploymentTarget::simulateDelay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
} 