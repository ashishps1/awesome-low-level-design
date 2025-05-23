#include "deployment_facade.h"
#include <iostream>

int main() {
    DeploymentFacade facade;

    // Example 1: Full deployment
    std::cout << "=== Full Deployment Example ===" << std::endl;
    facade.deployApplication("main", "production-server");

    // Example 2: Hotfix deployment
    std::cout << "\n=== Hotfix Deployment Example ===" << std::endl;
    facade.deployHotfix("hotfix/security-patch", "production-server");

    return 0;
} 