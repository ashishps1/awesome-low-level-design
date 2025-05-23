#pragma once
#include "version_control_system.h"
#include "build_system.h"
#include "testing_framework.h"
#include "deployment_target.h"
#include <string>
#include <memory>

class DeploymentFacade {
public:
    DeploymentFacade();
    bool deployApplication(const std::string& branch, const std::string& serverAddress);
    bool deployHotfix(const std::string& branch, const std::string& serverAddress);

private:
    std::unique_ptr<VersionControlSystem> vcs;
    std::unique_ptr<BuildSystem> buildSystem;
    std::unique_ptr<TestingFramework> testingFramework;
    std::unique_ptr<DeploymentTarget> deploymentTarget;
}; 