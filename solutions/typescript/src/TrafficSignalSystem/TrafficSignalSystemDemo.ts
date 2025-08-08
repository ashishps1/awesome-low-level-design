import { DirectionEnum } from "./Direction";
import Intersection from "./Intersection";
import TrafficLight from "./TrafficLight";

export default class TrafficSignalSystemDemo {
    static run() {
        // Configure durations per direction and state
        const signalDurations = new Map<DirectionEnum, Map<string, number>>([
            [
                DirectionEnum.NORTH,
                new Map([
                    ["GREEN", 4],
                    ["YELLOW", 2],
                    ["RED", 3],
                ]),
            ],
            [
                DirectionEnum.SOUTH,
                new Map([
                    ["GREEN", 3],
                    ["YELLOW", 2],
                    ["RED", 4],
                ]),
            ],
            [
                DirectionEnum.EAST,
                new Map([
                    ["GREEN", 5],
                    ["YELLOW", 2],
                    ["RED", 3],
                ]),
            ],
            [
                DirectionEnum.WEST,
                new Map([
                    ["GREEN", 2],
                    ["YELLOW", 2],
                    ["RED", 5],
                ]),
            ],
        ]);

        // Initialize traffic lights
        const signals = new Map<DirectionEnum, TrafficLight>();
        for (const direction of Object.values(DirectionEnum)) {
            signals.set(direction, new TrafficLight(direction));
        }

        // Create and start the controller
        const intersection1 = new Intersection("1", signals, signalDurations);
        intersection1.start(DirectionEnum.NORTH);
    }
}
