package trafficsignalcontrolsystem.states.light;

import trafficsignalcontrolsystem.TrafficLight;
import trafficsignalcontrolsystem.enums.LightColor;

public class YellowState implements SignalState {
    @Override
    public void handle(TrafficLight context) {
        context.setColor(LightColor.YELLOW);
        // After being yellow, the next state is red.
        context.setNextState(new RedState());
    }
}
