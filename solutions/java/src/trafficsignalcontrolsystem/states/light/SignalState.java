package trafficsignalcontrolsystem.states.light;

import trafficsignalcontrolsystem.TrafficLight;

public interface SignalState {
    void handle(TrafficLight context);
}
