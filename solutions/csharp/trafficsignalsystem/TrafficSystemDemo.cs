using System;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Collections.Generic;

public class TrafficSystemDemo
{
    public static void Main(string[] args)
    {
        // 1. Get the singleton TrafficControlSystem instance
        TrafficControlSystem system = TrafficControlSystem.GetInstance();

        // 2. Add intersections to the system
        system.AddIntersection(1, 500, 200);
        system.AddIntersection(2, 700, 150);

        // 3. Start the system
        system.StartSystem();

        // 4. Let the simulation run for a while (e.g., 5 seconds)
        try
        {
            Thread.Sleep(5000);
        }
        catch (ThreadInterruptedException)
        {
            Thread.CurrentThread.Interrupt();
        }

        // 5. Stop the system gracefully
        system.StopSystem();
    }
}