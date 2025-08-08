package trafficsignalcontrolsystem;

import trafficsignalcontrolsystem.observer.CentralMonitor;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class TrafficControlSystem {
    private static final TrafficControlSystem INSTANCE = new TrafficControlSystem();
    private final List<IntersectionController> intersections = new ArrayList<>();
    private ExecutorService executorService;

    private TrafficControlSystem() {}

    public static TrafficControlSystem getInstance() {
        return INSTANCE;
    }

    public void addIntersection(int intersectionId, int greenDuration, int yellowDuration) {
        IntersectionController intersection = new IntersectionController.Builder(intersectionId)
                .withDurations(greenDuration, yellowDuration)
                .addObserver(new CentralMonitor())
                .build();
        intersections.add(intersection);
    }

    public void startSystem() {
        if (intersections.isEmpty()) {
            System.out.println("No intersections to manage. System not starting.");
            return;
        }
        System.out.println("--- Starting Traffic Control System ---");
        executorService = Executors.newFixedThreadPool(intersections.size());
        intersections.forEach(executorService::submit);
    }

    public void stopSystem() {
        System.out.println("\n--- Shutting Down Traffic Control System ---");
        intersections.forEach(IntersectionController::stop);
        executorService.shutdown();
        try {
            if (!executorService.awaitTermination(5, TimeUnit.SECONDS)) {
                executorService.shutdownNow();
            }
        } catch (InterruptedException e) {
            executorService.shutdownNow();
        }
        System.out.println("All intersections stopped. System shut down.");
    }
}
