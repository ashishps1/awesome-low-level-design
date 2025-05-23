using System;
using System.Threading;

namespace Facade
{
    public class TestingFramework
    {
        public bool RunUnitTests()
        {
            Console.WriteLine("Testing: Running unit tests...");
            SimulateDelay(1500);
            Console.WriteLine("Testing: Unit tests passed.");
            return true;
        }

        public bool RunIntegrationTests()
        {
            Console.WriteLine("Testing: Running integration tests...");
            SimulateDelay(3000);
            Console.WriteLine("Testing: Integration tests passed.");
            return true;
        }

        private void SimulateDelay(int ms)
        {
            Thread.Sleep(ms);
        }
    }
} 