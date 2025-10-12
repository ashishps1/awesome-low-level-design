package trafficsignalcontrolsystem;

import java.util.concurrent.TimeUnit;

public class TrafficSystemDemo {
    public static void main(String[] args) {
        // 1. Get the singleton TrafficControlSystem instance
        TrafficControlSystem system = TrafficControlSystem.getInstance();

        // 2. Add intersections to the system
        system.addIntersection(1, 500, 200);
        system.addIntersection(2, 700, 150);

        // 3. Start the system
        system.startSystem();

        // 4. Let the simulation run for a while (e.g., 5 seconds)
        try {
            TimeUnit.SECONDS.sleep(5);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        // 5. Stop the system gracefully
        system.stopSystem();
    }
}
