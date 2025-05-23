using System;
using System.Threading;

namespace Facade
{
    public class DeploymentTarget
    {
        public void TransferArtifact(string artifactPath, string server)
        {
            Console.WriteLine($"Deployment: Transferring {artifactPath} to {server}...");
            SimulateDelay(1000);
            Console.WriteLine("Deployment: Transfer complete.");
        }

        public void ActivateNewVersion(string server)
        {
            Console.WriteLine($"Deployment: Activating new version on {server}...");
            SimulateDelay(500);
            Console.WriteLine($"Deployment: Now live on {server}!");
        }

        private void SimulateDelay(int ms)
        {
            Thread.Sleep(ms);
        }
    }
} 