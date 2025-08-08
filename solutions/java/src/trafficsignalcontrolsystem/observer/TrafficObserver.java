package trafficsignalcontrolsystem.observer;

import trafficsignalcontrolsystem.enums.Direction;
import trafficsignalcontrolsystem.enums.LightColor;

public interface TrafficObserver {
    void update(int intersectionId, Direction direction, LightColor color);
}
