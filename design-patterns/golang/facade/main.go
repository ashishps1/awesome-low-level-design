package facade

import "fmt"

func main() {
	// Create the deployment facade
	deploymentFacade := NewDeploymentFacade()

	// Perform a full deployment
	fmt.Println("=== Performing Full Deployment ===")
	success := deploymentFacade.DeployApplication("main", "production-server")
	if !success {
		fmt.Println("Full deployment failed!")
	}

	// Perform a hotfix deployment
	fmt.Println("\n=== Performing Hotfix Deployment ===")
	success = deploymentFacade.DeployHotfix("hotfix-123", "production-server")
	if !success {
		fmt.Println("Hotfix deployment failed!")
	}
}
