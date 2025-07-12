import { DirectionEnum } from "../Direction";
import TrafficLight from "../TrafficLight";
import TrafficSignalController from "../TrafficSignalController";

export default interface SignalState {
    handle(
        light: TrafficLight,
        controller: TrafficSignalController,
        direction: DirectionEnum,
    ): void;
    getName(): string;
}
