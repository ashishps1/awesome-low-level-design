public class DeploymentAppDirect {
    public static void main(String[] args) {
        DeploymentOrchestrator orchestrator = new DeploymentOrchestrator();
        orchestrator.deployApplication("main", "prod.server.example.com");

        System.out.println("\n--- Attempting another deployment ---");
        orchestrator.deployApplication("feature/new-ui", "staging.server.example.com");
    }
}
