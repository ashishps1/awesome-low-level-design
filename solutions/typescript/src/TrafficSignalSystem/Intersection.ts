import { DirectionEnum } from "./Direction";
import TrafficLight from "./TrafficLight";
import TrafficSignalController from "./TrafficSignalController";

export default class Intersection {
    private id: string;
    private signals: Map<DirectionEnum, TrafficLight>;
    private signalDurations: Map<DirectionEnum, Map<String, number>>;
    private controller: TrafficSignalController;

    constructor(
        id: string,
        signals: Map<DirectionEnum, TrafficLight>,
        signalDurations: Map<DirectionEnum, Map<String, number>>,
    ) {
        this.id = id;
        this.signals = signals;
        this.signalDurations = signalDurations;
        this.controller = new TrafficSignalController(signals, signalDurations);
    }

    start(startDirection: DirectionEnum) {
        this.controller.start(startDirection);
    }

    manualOverride(direction: DirectionEnum) {
        console.log("Manual override: Setting " + direction + " to GREEN.");
        this.controller.manualOverride(direction);
    }

    getSignal(direction: DirectionEnum) {
        return this.signals.get(direction);
    }
}
