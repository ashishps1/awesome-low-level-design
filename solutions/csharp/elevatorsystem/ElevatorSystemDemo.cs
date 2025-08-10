using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using System.Linq;

public class ElevatorSystemDemo
{
    public static void Main(string[] args)
    {
        // Setup: A building with 2 elevators
        int numElevators = 2;
        // The GetInstance method now initializes the elevators and attaches the Display (Observer).
        ElevatorSystem elevatorSystem = ElevatorSystem.GetInstance(numElevators);

        // Start the elevator system
        elevatorSystem.Start();
        Console.WriteLine("Elevator system started. ConsoleDisplay is observing.\n");

        // --- SIMULATION START ---

        // 1. External Request: User at floor 5 wants to go UP.
        // The system will dispatch this to the nearest elevator (likely E1 or E2, both at floor 1).
        elevatorSystem.RequestElevator(5, Direction.UP);
        Thread.Sleep(100); // Wait for the elevator to start moving

        // 2. Internal Request: Assume E1 took the previous request.
        // The user gets in at floor 5 and presses 10.
        // We send this request directly to E1.

        // Note: In a real simulation, we'd wait until E1 reaches floor 5, but for this demo,
        // we simulate the internal button press shortly after the external one.
        elevatorSystem.SelectFloor(1, 10);
        Thread.Sleep(200);

        // 3. External Request: User at floor 3 wants to go DOWN.
        // E2 (likely still idle at floor 1) might take this, or E1 if it's convenient.
        elevatorSystem.RequestElevator(3, Direction.DOWN);
        Thread.Sleep(300);

        // 4. Internal Request: User in E2 presses 1.
        elevatorSystem.SelectFloor(2, 1);

        // Let the simulation run for a while to observe the display updates
        Console.WriteLine("\n--- Letting simulation run for 1 second ---");
        Thread.Sleep(1000);

        // Shutdown the system
        elevatorSystem.Shutdown();
        Console.WriteLine("\n--- SIMULATION END ---");
    }
}