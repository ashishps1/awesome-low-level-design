package trafficsignalsystem;

import java.util.EnumMap;
import java.util.Map;

public class TrafficSignalSystemDemo {
    public static void run() {
        // Configure signal durations per direction
        Map<Direction, Map<SignalState, Integer>> signalDurations = new EnumMap<>(Direction.class);

        // Example: Different durations for each direction
        signalDurations.put(Direction.NORTH, Map.of(
                SignalState.GREEN, 4,
                SignalState.YELLOW, 2,
                SignalState.RED, 3
        ));
        signalDurations.put(Direction.SOUTH, Map.of(
                SignalState.GREEN, 3,
                SignalState.YELLOW, 2,
                SignalState.RED, 4
        ));
        signalDurations.put(Direction.EAST, Map.of(
                SignalState.GREEN, 5,
                SignalState.YELLOW, 2,
                SignalState.RED, 3
        ));
        signalDurations.put(Direction.WEST, Map.of(
                SignalState.GREEN, 2,
                SignalState.YELLOW, 2,
                SignalState.RED, 5
        ));

        // Initialize controller with one signal per direction
        Map<Direction, TrafficLight> signals = new EnumMap<>(Direction.class);
        for (Direction direction : Direction.values()) {
            signals.put(direction, new TrafficLight());
        }

        Intersection intersection1 = new Intersection("1", signals, signalDurations);

        // Start the traffic signal simulation
        System.out.println("Starting traffic signal controller...\n");
        intersection1.start();
    }
}
