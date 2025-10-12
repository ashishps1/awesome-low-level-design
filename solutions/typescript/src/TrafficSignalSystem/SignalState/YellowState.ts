import { DirectionEnum } from "../Direction";
import TrafficLight from "../TrafficLight";
import TrafficSignalController from "../TrafficSignalController";
import RedState from "./RedState";
import SignalState from "./SignalState";

export default class YellowState implements SignalState {
    handle(
        light: TrafficLight,
        controller: TrafficSignalController,
        direction: DirectionEnum,
    ) {
        console.log("Direction: " + direction + " | State: YELLOW");
        const duration = controller.getSignalDuration(direction, this);
        controller.scheduleStateChange(
            light,
            direction,
            new RedState(),
            duration,
        );
    }

    getName() {
        return "YELLOW";
    }
}
