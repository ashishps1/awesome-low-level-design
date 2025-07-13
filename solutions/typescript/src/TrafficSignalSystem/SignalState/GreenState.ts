import { DirectionEnum } from "../Direction";
import TrafficLight from "../TrafficLight";
import TrafficSignalController from "../TrafficSignalController";
import SignalState from "./SignalState";
import YellowState from "./YellowState";

export default class GreenState implements SignalState {
    handle(
        light: TrafficLight,
        controller: TrafficSignalController,
        direction: DirectionEnum,
    ) {
        console.log("Direction: " + direction + " | State: GREEN");
        const duration = controller.getSignalDuration(direction, this);
        controller.scheduleStateChange(
            light,
            direction,
            new YellowState(),
            duration,
        );
    }

    getName() {
        return "GREEN";
    }
}
