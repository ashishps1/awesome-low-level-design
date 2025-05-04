package trafficsignalsystem;

import java.util.Map;

public class Intersection {
    private final String id;
    private Map<Direction, TrafficLight> signals;
    private final TrafficSignalController controller;

    public Intersection(String id, Map<Direction, TrafficLight> signals, Map<Direction, Map<SignalState, Integer>> signalDurations) {
        this.id = id;
        this.signals = signals;
        this.controller = new TrafficSignalController(signals, signalDurations);
    }

    public void start() {
        controller.start();
    }

    public void manualOverride(Direction direction) {
        controller.override(direction);
    }

    public TrafficLight getSignal(Direction direction) {
        return signals.get(direction);
    }
}
