#include "deployment_facade.h"
#include <iostream>

DeploymentFacade::DeploymentFacade()
    : vcs(std::make_unique<VersionControlSystem>())
    , buildSystem(std::make_unique<BuildSystem>())
    , testingFramework(std::make_unique<TestingFramework>())
    , deploymentTarget(std::make_unique<DeploymentTarget>()) {}

bool DeploymentFacade::deployApplication(const std::string& branch, const std::string& serverAddress) {
    std::cout << "\nFACADE: --- Initiating FULL DEPLOYMENT for branch: " << branch << " to " << serverAddress << " ---" << std::endl;
    bool success = true;

    try {
        // Step 1: Pull latest code
        vcs->pullLatestChanges(branch);

        // Step 2: Build the project
        if (!buildSystem->compileProject()) {
            std::cerr << "FACADE: DEPLOYMENT FAILED - Build compilation failed." << std::endl;
            return false;
        }
        std::string artifactPath = buildSystem->getArtifactPath();

        // Step 3: Run tests
        if (!testingFramework->runUnitTests()) {
            std::cerr << "FACADE: DEPLOYMENT FAILED - Unit tests failed." << std::endl;
            return false;
        }
        if (!testingFramework->runIntegrationTests()) {
            std::cerr << "FACADE: DEPLOYMENT FAILED - Integration tests failed." << std::endl;
            return false;
        }

        // Step 4: Deploy to production
        deploymentTarget->transferArtifact(artifactPath, serverAddress);
        deploymentTarget->activateNewVersion(serverAddress);

        std::cout << "FACADE: APPLICATION DEPLOYED SUCCESSFULLY TO " << serverAddress << "!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "FACADE: DEPLOYMENT FAILED - An unexpected error occurred: " << e.what() << std::endl;
        success = false;
    }
    return success;
}

bool DeploymentFacade::deployHotfix(const std::string& branch, const std::string& serverAddress) {
    std::cout << "\nFACADE: --- Initiating HOTFIX DEPLOYMENT for branch: " << branch << " to " << serverAddress << " ---" << std::endl;
    bool success = true;

    try {
        // Step 1: Pull latest code
        vcs->pullLatestChanges(branch);

        // Step 2: Build the project
        if (!buildSystem->compileProject()) {
            std::cerr << "FACADE: HOTFIX FAILED - Build compilation failed." << std::endl;
            return false;
        }
        std::string artifactPath = buildSystem->getArtifactPath();

        // Step 3: For a hotfix, we skip extensive tests
        std::cout << "FACADE: Skipping full test suite for hotfix deployment (or running minimal smoke tests)." << std::endl;

        // Step 4: Deploy to production
        deploymentTarget->transferArtifact(artifactPath, serverAddress);
        deploymentTarget->activateNewVersion(serverAddress);

        std::cout << "FACADE: HOTFIX DEPLOYED SUCCESSFULLY TO " << serverAddress << "!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "FACADE: HOTFIX FAILED - An unexpected error occurred: " << e.what() << std::endl;
        success = false;
    }
    return success;
} 