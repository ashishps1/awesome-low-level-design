from .version_control_system import VersionControlSystem
from .build_system import BuildSystem
from .testing_framework import TestingFramework
from .deployment_target import DeploymentTarget

def main():
    # Create all the components
    vcs = VersionControlSystem()
    build_system = BuildSystem()
    testing = TestingFramework()
    deployment = DeploymentTarget()
    
    # Deploy to production
    print("Deploying to production...")
    
    # Step 1: Get latest code
    vcs.pull_latest_changes("main")
    
    # Step 2: Build the project
    if not build_system.compile_project():
        print("Deployment failed: Build error")
        return
    
    # Step 3: Run tests
    if not testing.run_unit_tests():
        print("Deployment failed: Unit tests failed")
        return
        
    if not testing.run_integration_tests():
        print("Deployment failed: Integration tests failed")
        return
    
    # Step 4: Deploy to server
    artifact_path = build_system.get_artifact_path()
    deployment.transfer_artifact(artifact_path, "production-server")
    deployment.activate_new_version("production-server")
    
    print("Deployment completed successfully!")

if __name__ == "__main__":
    main() 