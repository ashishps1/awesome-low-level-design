using System;

namespace Facade
{
    public class DeploymentFacade
    {
        private readonly VersionControlSystem vcs;
        private readonly BuildSystem buildSystem;
        private readonly TestingFramework testingFramework;
        private readonly DeploymentTarget deploymentTarget;

        public DeploymentFacade()
        {
            vcs = new VersionControlSystem();
            buildSystem = new BuildSystem();
            testingFramework = new TestingFramework();
            deploymentTarget = new DeploymentTarget();
        }

        public bool DeployApplication(string branch, string serverAddress)
        {
            Console.WriteLine($"\nFACADE: --- Initiating FULL DEPLOYMENT for branch: {branch} to {serverAddress} ---");
            bool success = true;

            try
            {
                // Step 1: Pull latest code
                vcs.PullLatestChanges(branch);

                // Step 2: Build the project
                if (!buildSystem.CompileProject())
                {
                    Console.Error.WriteLine("FACADE: DEPLOYMENT FAILED - Build compilation failed.");
                    return false;
                }
                string artifactPath = buildSystem.GetArtifactPath();

                // Step 3: Run tests
                if (!testingFramework.RunUnitTests())
                {
                    Console.Error.WriteLine("FACADE: DEPLOYMENT FAILED - Unit tests failed.");
                    return false;
                }
                if (!testingFramework.RunIntegrationTests())
                {
                    Console.Error.WriteLine("FACADE: DEPLOYMENT FAILED - Integration tests failed.");
                    return false;
                }

                // Step 4: Deploy to production
                deploymentTarget.TransferArtifact(artifactPath, serverAddress);
                deploymentTarget.ActivateNewVersion(serverAddress);

                Console.WriteLine($"FACADE: APPLICATION DEPLOYED SUCCESSFULLY TO {serverAddress}!");
            }
            catch (Exception e)
            {
                Console.Error.WriteLine($"FACADE: DEPLOYMENT FAILED - An unexpected error occurred: {e.Message}");
                success = false;
            }
            return success;
        }

        public bool DeployHotfix(string branch, string serverAddress)
        {
            Console.WriteLine($"\nFACADE: --- Initiating HOTFIX DEPLOYMENT for branch: {branch} to {serverAddress} ---");
            bool success = true;

            try
            {
                // Step 1: Pull latest code
                vcs.PullLatestChanges(branch);

                // Step 2: Build the project
                if (!buildSystem.CompileProject())
                {
                    Console.Error.WriteLine("FACADE: HOTFIX FAILED - Build compilation failed.");
                    return false;
                }
                string artifactPath = buildSystem.GetArtifactPath();

                // Step 3: For a hotfix, we might skip extensive tests or run a specific "smoke test" suite.
                Console.WriteLine("FACADE: Skipping full test suite for hotfix deployment (or running minimal smoke tests).");

                // Step 4: Deploy to production
                deploymentTarget.TransferArtifact(artifactPath, serverAddress);
                deploymentTarget.ActivateNewVersion(serverAddress);

                Console.WriteLine($"FACADE: HOTFIX DEPLOYED SUCCESSFULLY TO {serverAddress}!");
            }
            catch (Exception e)
            {
                Console.Error.WriteLine($"FACADE: HOTFIX FAILED - An unexpected error occurred: {e.Message}");
                success = false;
            }
            return success;
        }
    }
} 