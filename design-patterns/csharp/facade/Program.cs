using System;

namespace Facade
{
    class Program
    {
        static void Main(string[] args)
        {
            var deploymentFacade = new DeploymentFacade();

            // Demonstrate full deployment
            Console.WriteLine("=== Full Deployment Example ===");
            deploymentFacade.DeployApplication("main", "production-server");

            // Demonstrate hotfix deployment
            Console.WriteLine("\n=== Hotfix Deployment Example ===");
            deploymentFacade.DeployHotfix("hotfix/security-patch", "production-server");
        }
    }
} 