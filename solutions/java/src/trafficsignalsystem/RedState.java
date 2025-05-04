package trafficsignalsystem;

public class RedState implements SignalState {
    @Override
    public void handle(TrafficLight light, TrafficSignalController controller, Direction direction) {
        System.out.println("Direction: " + direction + " | State: RED");
        int duration = controller.getSignalDuration(direction, this);
        // After RED, move to next direction's GREEN
        Direction nextDirection = controller.getNextDirection(direction);
        controller.scheduleStateChange(
            controller.getTrafficLight(nextDirection),
            nextDirection,
            new GreenState(),
            duration
        );
    }
    @Override
    public String getName() { return "RED"; }
} 