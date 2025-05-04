package trafficsignalsystem;

import java.util.EnumMap;
import java.util.Map;

public class TrafficSignalSystemDemo {
    public static void run() {
        // Configure durations per direction and state
        Map<Direction, Map<String, Integer>> signalDurations = new EnumMap<>(Direction.class);
        signalDurations.put(Direction.NORTH, Map.of("GREEN", 4, "YELLOW", 2, "RED", 3));
        signalDurations.put(Direction.SOUTH, Map.of("GREEN", 3, "YELLOW", 2, "RED", 4));
        signalDurations.put(Direction.EAST, Map.of("GREEN", 5, "YELLOW", 2, "RED", 3));
        signalDurations.put(Direction.WEST, Map.of("GREEN", 2, "YELLOW", 2, "RED", 5));

        // Initialize traffic lights
        Map<Direction, TrafficLight> signals = new EnumMap<>(Direction.class);
        for (Direction direction : Direction.values()) {
            signals.put(direction, new TrafficLight(direction));
        }

        // Create and start the controller
        Intersection intersection1 = new Intersection("1", signals, signalDurations);
        intersection1.start(Direction.NORTH);
    }
}
