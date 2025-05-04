package trafficsignalsystem;

import java.util.Map;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class TrafficSignalController {
    private final Map<Direction, TrafficLight> signals;
    private final Map<Direction, Map<SignalState, Integer>> signalDurations;
    private final ScheduledExecutorService scheduler = Executors.newSingleThreadScheduledExecutor();

    public TrafficSignalController(Map<Direction, TrafficLight> signals, Map<Direction, Map<SignalState, Integer>> signalDurations) {
        this.signals = signals;
        this.signalDurations = signalDurations;
    }

    public void start() {
        // Start with GREEN for NORTH (or any direction you prefer)
        rotateSignal(Direction.NORTH, SignalState.GREEN);
    }

    private void rotateSignal(Direction direction, SignalState state) {
        signals.get(direction).changeSignal(state);

        int duration = signalDurations.get(direction).get(state);

        SignalState nextState;
        Direction nextDirection = direction;

        switch (state) {
            case GREEN:
                nextState = SignalState.YELLOW;
                break;
            case YELLOW:
                nextState = SignalState.RED;
                break;
            case RED:
                nextState = SignalState.GREEN;
                nextDirection = getNextDirection(direction);
                break;
            default:
                throw new IllegalStateException("Unknown state: " + state);
        }

        // Print current state for demo/logging
        System.out.println("Direction: " + direction + " | State: " + state + " | Duration: " + duration + "s");

        // Schedule the next state transition
        Direction finalNextDirection = nextDirection;
        scheduler.schedule(() -> rotateSignal(finalNextDirection, nextState), duration, TimeUnit.SECONDS);
    }

    private Direction getNextDirection(Direction current) {
        Direction[] directions = Direction.values();
        int next = (current.ordinal() + 1) % directions.length;
        return directions[next];
    }

    public void override(Direction direction) {
        scheduler.execute(() -> rotateSignal(direction, SignalState.GREEN));
    }
}
