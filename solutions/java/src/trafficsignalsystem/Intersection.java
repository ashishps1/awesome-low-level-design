package trafficsignalsystem;

import java.util.Map;

public class Intersection {
    private final String id;
    private final Map<Direction, TrafficLight> signals;
    private final Map<Direction, Map<String, Integer>> signalDurations;
    private final TrafficSignalController controller;

    public Intersection(String id, Map<Direction, TrafficLight> signals, Map<Direction, Map<String, Integer>> signalDurations) {
        this.id = id;
        this.signals = signals;
        this.signalDurations = signalDurations;
        this.controller = new TrafficSignalController(signals, signalDurations);
    }

    public void start(Direction startDirection) {
        controller.start(startDirection);
    }

    public void manualOverride(Direction direction) {
        System.out.println("Manual override: Setting " + direction + " to GREEN.");
        controller.manualOverride(direction);
    }

    public TrafficLight getSignal(Direction direction) {
        return signals.get(direction);
    }
}
