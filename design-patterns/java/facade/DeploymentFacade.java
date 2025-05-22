public class DeploymentFacade {
    // Instances of all the subsystem components
    // or they can be injected (e.g., via constructor for better testability).
    private VersionControlSystem vcs = new VersionControlSystem();
    private BuildSystem buildSystem = new BuildSystem();
    private TestingFramework testingFramework = new TestingFramework();
    private DeploymentTarget deploymentTarget = new DeploymentTarget();

    // Perform a full standard deployment: pull, build, test, deploy.
    public boolean deployApplication(String branch, String serverAddress) {
        System.out.println("\nFACADE: --- Initiating FULL DEPLOYMENT for branch: " + branch + " to " + serverAddress + " ---");
        boolean success = true;

        try {
            // Step 1: Pull latest code
            vcs.pullLatestChanges(branch);

            // Step 2: Build the project
            if (!buildSystem.compileProject()) {
                System.err.println("FACADE: DEPLOYMENT FAILED - Build compilation failed.");
                return false; // Exit early on critical failure
            }
            String artifactPath = buildSystem.getArtifactPath();

            // Step 3: Run tests
            if (!testingFramework.runUnitTests()) {
                System.err.println("FACADE: DEPLOYMENT FAILED - Unit tests failed.");
                return false;
            }
            if (!testingFramework.runIntegrationTests()) {
                System.err.println("FACADE: DEPLOYMENT FAILED - Integration tests failed.");
                return false;
            }

            // Step 4: Deploy to production
            deploymentTarget.transferArtifact(artifactPath, serverAddress);
            deploymentTarget.activateNewVersion(serverAddress);

            System.out.println("FACADE: APPLICATION DEPLOYED SUCCESSFULLY TO " + serverAddress + "!");
        } catch (Exception e) {
            System.err.println("FACADE: DEPLOYMENT FAILED - An unexpected error occurred: " + e.getMessage());
            e.printStackTrace(); // Log the full stack trace
            success = false;
        }
        return success;
    }


    public boolean deployHotfix(String branch, String serverAddress) {
        System.out.println("\nFACADE: --- Initiating HOTFIX DEPLOYMENT for branch: " + branch + " to " + serverAddress + " ---");
        boolean success = true;
        try {
            // Step 1: Pull latest code
            vcs.pullLatestChanges(branch);

            // Step 2: Build the project
            if (!buildSystem.compileProject()) {
                System.err.println("FACADE: HOTFIX FAILED - Build compilation failed.");
                return false;
            }
            String artifactPath = buildSystem.getArtifactPath();

            // Step 3: For a hotfix, we might skip extensive tests or run a specific "smoke test" suite.
            System.out.println("FACADE: Skipping full test suite for hotfix deployment (or running minimal smoke tests).");
            // if (!testingFramework.runSmokeTests()) { return false; } // Example

            // Step 4: Deploy to production
            deploymentTarget.transferArtifact(artifactPath, serverAddress);
            deploymentTarget.activateNewVersion(serverAddress);

            System.out.println("FACADE: HOTFIX DEPLOYED SUCCESSFULLY TO " + serverAddress + "!");
        } catch (Exception e) {
            System.err.println("FACADE: HOTFIX FAILED - An unexpected error occurred: " + e.getMessage());
            success = false;
        }
        return success;
    }
    // We could add other simplified methods: rollbackLastDeployment(), checkDeploymentStatus(), etc.
}
