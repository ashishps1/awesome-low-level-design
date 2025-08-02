import { DirectionEnum } from "../Direction";
import TrafficLight from "../TrafficLight";
import TrafficSignalController from "../TrafficSignalController";
import GreenState from "./GreenState";
import SignalState from "./SignalState";

export default class RedState implements SignalState {
    handle(
        light: TrafficLight,
        controller: TrafficSignalController,
        direction: DirectionEnum,
    ) {
        console.log("Direction: " + direction + " | State: RED");
        const duration = controller.getSignalDuration(direction, this);

        // After RED, move to next direction's GREEN
        const nextDirection = controller.getNextDirection(direction);
        controller.scheduleStateChange(
            controller.getTrafficLight(nextDirection),
            nextDirection,
            new GreenState(),
            duration,
        );
    }

    getName() {
        return "RED";
    }
}
