package elevatorsystem;

import elevatorsystem.enums.Direction;

public class ElevatorSystemDemo {
    public static void main(String[] args) throws InterruptedException {
        // Setup: A building with 2 elevators
        int numElevators = 2;
        // The getInstance method now initializes the elevators and attaches the Display (Observer).
        ElevatorSystem elevatorSystem = ElevatorSystem.getInstance(numElevators);

        // Start the elevator system
        elevatorSystem.start();
        System.out.println("Elevator system started. ConsoleDisplay is observing.\n");

        // --- SIMULATION START ---

        // 1. External Request: User at floor 5 wants to go UP.
        // The system will dispatch this to the nearest elevator (likely E1 or E2, both at floor 1).
        elevatorSystem.requestElevator(5, Direction.UP);
        Thread.sleep(100); // Wait for the elevator to start moving

        // 2. Internal Request: Assume E1 took the previous request.
        // The user gets in at floor 5 and presses 10.
        // We send this request directly to E1.

        // Note: In a real simulation, we'd wait until E1 reaches floor 5, but for this demo,
        // we simulate the internal button press shortly after the external one.
        elevatorSystem.selectFloor(1, 10);
        Thread.sleep(200);

        // 3. External Request: User at floor 3 wants to go DOWN.
        // E2 (likely still idle at floor 1) might take this, or E1 if it's convenient.
        elevatorSystem.requestElevator(3, Direction.DOWN);
        Thread.sleep(300);

        // 4. Internal Request: User in E2 presses 1.
        elevatorSystem.selectFloor(2, 1);

        // Let the simulation run for a while to observe the display updates
        System.out.println("\n--- Letting simulation run for 1 second ---");
        Thread.sleep(1000);

        // Shutdown the system
        elevatorSystem.shutdown();
        System.out.println("\n--- SIMULATION END ---");
    }
}