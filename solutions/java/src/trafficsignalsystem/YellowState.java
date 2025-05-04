package trafficsignalsystem;

public class YellowState implements SignalState {
    @Override
    public void handle(TrafficLight light, TrafficSignalController controller, Direction direction) {
        System.out.println("Direction: " + direction + " | State: YELLOW");
        int duration = controller.getSignalDuration(direction, this);
        controller.scheduleStateChange(light, direction, new RedState(), duration);
    }
    @Override
    public String getName() { return "YELLOW"; }
} 