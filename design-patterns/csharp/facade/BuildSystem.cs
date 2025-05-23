using System;
using System.Threading;

namespace Facade
{
    public class BuildSystem
    {
        public bool CompileProject()
        {
            Console.WriteLine("BuildSystem: Compiling project...");
            SimulateDelay(2000);
            Console.WriteLine("BuildSystem: Build successful.");
            return true;
        }

        public string GetArtifactPath()
        {
            string path = "target/myapplication-1.0.jar";
            Console.WriteLine($"BuildSystem: Artifact located at {path}");
            return path;
        }
        
        private void SimulateDelay(int ms)
        {
            Thread.Sleep(ms);
        }
    }
} 