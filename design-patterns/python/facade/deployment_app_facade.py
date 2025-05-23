from .deployment_facade import DeploymentFacade

def main():
    # Create the facade
    deployment = DeploymentFacade()
    
    # Deploy to production
    print("Deploying to production...")
    deployment.deploy("main", "production-server")
    
    # Deploy to staging
    print("\nDeploying to staging...")
    deployment.deploy("develop", "staging-server")

if __name__ == "__main__":
    main() 