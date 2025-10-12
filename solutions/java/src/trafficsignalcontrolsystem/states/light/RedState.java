package trafficsignalcontrolsystem.states.light;

import trafficsignalcontrolsystem.TrafficLight;
import trafficsignalcontrolsystem.enums.LightColor;

public class RedState implements SignalState {
    @Override
    public void handle(TrafficLight context) {
        context.setColor(LightColor.RED);
        // Red is a stable state, it transitions to green only when the intersection controller commands it.
        // So, the next state is self.
        context.setNextState(new RedState());
    }
}
