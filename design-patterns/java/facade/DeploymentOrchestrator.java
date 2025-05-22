public class DeploymentOrchestrator {
    private VersionControlSystem vcs = new VersionControlSystem();
    private BuildSystem buildSystem = new BuildSystem();
    private TestingFramework testFramework = new TestingFramework();
    private DeploymentTarget deployTarget = new DeploymentTarget();

    public boolean deployApplication(String branch, String prodServer) {
        System.out.println("\n[Orchestrator] Starting deployment for branch: " + branch);

        vcs.pullLatestChanges(branch);

        if (!buildSystem.compileProject()) {
            System.err.println("Build failed. Deployment aborted.");
            return false;
        }

        String artifact = buildSystem.getArtifactPath();

        if (!testFramework.runUnitTests() || !testFramework.runIntegrationTests()) {
            System.err.println("Tests failed. Deployment aborted.");
            return false;
        }

        deployTarget.transferArtifact(artifact, prodServer);
        deployTarget.activateNewVersion(prodServer);

        System.out.println("[Orchestrator] Deployment successful!");
        return true;
    }    
}