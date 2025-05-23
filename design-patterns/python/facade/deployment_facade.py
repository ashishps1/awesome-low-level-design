from .version_control_system import VersionControlSystem
from .build_system import BuildSystem
from .testing_framework import TestingFramework
from .deployment_target import DeploymentTarget

class DeploymentFacade:
    def __init__(self):
        self.vcs = VersionControlSystem()
        self.build_system = BuildSystem()
        self.testing = TestingFramework()
        self.deployment = DeploymentTarget()

    def deploy(self, branch: str, server: str) -> None:
        print("Starting deployment process...")
        
        # Step 1: Get latest code
        self.vcs.pull_latest_changes(branch)
        
        # Step 2: Build the project
        if not self.build_system.compile_project():
            print("Deployment failed: Build error")
            return
        
        # Step 3: Run tests
        if not self.testing.run_unit_tests():
            print("Deployment failed: Unit tests failed")
            return
            
        if not self.testing.run_integration_tests():
            print("Deployment failed: Integration tests failed")
            return
        
        # Step 4: Deploy to server
        artifact_path = self.build_system.get_artifact_path()
        self.deployment.transfer_artifact(artifact_path, server)
        self.deployment.activate_new_version(server)
        
        print("Deployment completed successfully!") 