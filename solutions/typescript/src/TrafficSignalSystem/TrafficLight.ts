import { DirectionEnum } from "./Direction";
import RedState from "./SignalState/RedState";
import SignalState from "./SignalState/SignalState";
import TrafficSignalController from "./TrafficSignalController";

export default class TrafficLight {
    private state: SignalState;
    private direction: DirectionEnum;

    constructor(direction: DirectionEnum) {
        this.direction = direction;
        this.state = new RedState(); // Default initial state
    }

    setState(state: SignalState) {
        this.state = state;
    }

    getState() {
        return this.state;
    }

    getDirection() {
        return this.direction;
    }

    handle(controller: TrafficSignalController) {
        this.state.handle(this, controller, this.direction);
    }
}
