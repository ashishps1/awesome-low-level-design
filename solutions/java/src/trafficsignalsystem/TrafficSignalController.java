package trafficsignalsystem;

import java.util.Map;
import java.util.EnumMap;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class TrafficSignalController {
    private final Map<Direction, TrafficLight> signals;
    private final Map<Direction, Map<String, Integer>> signalDurations;
    private final ScheduledExecutorService scheduler = Executors.newSingleThreadScheduledExecutor();

    public TrafficSignalController(Map<Direction, TrafficLight> signals, Map<Direction, Map<String, Integer>> signalDurations) {
        this.signals = signals;
        this.signalDurations = signalDurations;
    }

    public void start(Direction startDirection) {
        TrafficLight light = signals.get(startDirection);
        light.setState(new GreenState());
        light.handle(this);
    }

    public void scheduleStateChange(TrafficLight light, Direction direction, SignalState nextState, int delaySeconds) {
        scheduler.schedule(() -> {
            light.setState(nextState);
            light.handle(this);
        }, delaySeconds, TimeUnit.SECONDS);
    }

    public int getSignalDuration(Direction direction, SignalState state) {
        return signalDurations.get(direction).get(state.getName());
    }

    public Direction getNextDirection(Direction current) {
        Direction[] directions = Direction.values();
        int next = (current.ordinal() + 1) % directions.length;
        return directions[next];
    }

    public TrafficLight getTrafficLight(Direction direction) {
        return signals.get(direction);
    }

    public void manualOverride(Direction direction) {
        // Immediately set the specified direction to GREEN and start its cycle
        TrafficLight light = signals.get(direction);
        light.setState(new GreenState());
        light.handle(this);
    }
}
