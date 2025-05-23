package facade

import "fmt"

// DeploymentFacade provides a simplified interface to the deployment system
type DeploymentFacade struct {
	vcs              *VersionControlSystem
	buildSystem      *BuildSystem
	testingFramework *TestingFramework
	deploymentTarget *DeploymentTarget
}

// NewDeploymentFacade creates a new DeploymentFacade instance
func NewDeploymentFacade() *DeploymentFacade {
	return &DeploymentFacade{
		vcs:              NewVersionControlSystem(),
		buildSystem:      NewBuildSystem(),
		testingFramework: NewTestingFramework(),
		deploymentTarget: NewDeploymentTarget(),
	}
}

// DeployApplication performs a full standard deployment
func (f *DeploymentFacade) DeployApplication(branch, serverAddress string) bool {
	fmt.Printf("\nFACADE: --- Initiating FULL DEPLOYMENT for branch: %s to %s ---\n", branch, serverAddress)
	success := true

	// Step 1: Pull latest code
	f.vcs.PullLatestChanges(branch)

	// Step 2: Build the project
	if !f.buildSystem.CompileProject() {
		fmt.Println("FACADE: DEPLOYMENT FAILED - Build compilation failed.")
		return false
	}
	artifactPath := f.buildSystem.GetArtifactPath()

	// Step 3: Run tests
	if !f.testingFramework.RunUnitTests() {
		fmt.Println("FACADE: DEPLOYMENT FAILED - Unit tests failed.")
		return false
	}
	if !f.testingFramework.RunIntegrationTests() {
		fmt.Println("FACADE: DEPLOYMENT FAILED - Integration tests failed.")
		return false
	}

	// Step 4: Deploy to production
	f.deploymentTarget.TransferArtifact(artifactPath, serverAddress)
	f.deploymentTarget.ActivateNewVersion(serverAddress)

	fmt.Printf("FACADE: APPLICATION DEPLOYED SUCCESSFULLY TO %s!\n", serverAddress)
	return success
}

// DeployHotfix performs a hotfix deployment
func (f *DeploymentFacade) DeployHotfix(branch, serverAddress string) bool {
	fmt.Printf("\nFACADE: --- Initiating HOTFIX DEPLOYMENT for branch: %s to %s ---\n", branch, serverAddress)
	success := true

	// Step 1: Pull latest code
	f.vcs.PullLatestChanges(branch)

	// Step 2: Build the project
	if !f.buildSystem.CompileProject() {
		fmt.Println("FACADE: HOTFIX FAILED - Build compilation failed.")
		return false
	}
	artifactPath := f.buildSystem.GetArtifactPath()

	// Step 3: Skip extensive tests for hotfix
	fmt.Println("FACADE: Skipping full test suite for hotfix deployment (or running minimal smoke tests).")

	// Step 4: Deploy to production
	f.deploymentTarget.TransferArtifact(artifactPath, serverAddress)
	f.deploymentTarget.ActivateNewVersion(serverAddress)

	fmt.Printf("FACADE: HOTFIX DEPLOYED SUCCESSFULLY TO %s!\n", serverAddress)
	return success
}
