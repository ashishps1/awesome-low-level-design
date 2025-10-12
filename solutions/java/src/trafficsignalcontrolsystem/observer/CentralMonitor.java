package trafficsignalcontrolsystem.observer;

import trafficsignalcontrolsystem.enums.Direction;
import trafficsignalcontrolsystem.enums.LightColor;

public class CentralMonitor implements TrafficObserver {
    @Override
    public void update(int intersectionId, Direction direction, LightColor color) {
        System.out.printf("[MONITOR] Intersection %d: Light for %s direction changed to %s.\n",
                intersectionId, direction, color);
    }
}
