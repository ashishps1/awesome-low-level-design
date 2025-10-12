# Traffic Signal System (LLD)

## Problem Statement

Design and implement a Traffic Signal System to manage the traffic lights at an intersection. The system should support configurable signal durations for each direction and state, automatic cycling of signals using the State design pattern, and the ability to manually override signals as needed.

---

## Requirements

- **Multiple Directions:** The intersection supports multiple directions (e.g., NORTH, SOUTH, EAST, WEST).
- **Traffic Light States:** Each direction has a traffic light with states: GREEN, YELLOW, RED.
- **Configurable Durations:** Each direction and state can have its own configurable duration.
- **Automatic Cycling:** The system automatically cycles through the states for each direction in a round-robin fashion.
- **Manual Override:** The system allows manual override to set a specific direction to GREEN at any time.
- **Extensibility:** Easy to add new directions or states if needed.
- **State Pattern:** Use the State design pattern to encapsulate state-specific behavior and transitions.

---

## Core Entities

- **Direction:** Enum representing the directions at the intersection (NORTH, SOUTH, EAST, WEST).
- **SignalState (interface):** Represents the state of a traffic light (GREEN, YELLOW, RED), with state-specific behavior.
- **GreenState, YellowState, RedState:** Concrete implementations of `SignalState` for each light state.
- **TrafficLight:** Represents a traffic light for a direction, maintains its current state and delegates behavior to the state.
- **Intersection:** Represents the intersection, holds all traffic lights and their configurations, and exposes the manual override.
- **TrafficSignalController:** Controls the cycling and overriding of traffic signals, manages timing and transitions using a scheduler.

---

## Class Design

### UML Class Diagram

![](../../../../uml-diagrams/class-diagrams/trafficsignalsystem-class-diagram.png)

### 1. Direction
- Enum: NORTH, SOUTH, EAST, WEST

### 2. SignalState (interface)
- **Methods:** `void handle(TrafficLight, TrafficSignalController, Direction)`, `String getName()`

### 3. GreenState, YellowState, RedState
- Implement `SignalState`
- Each handles its own transition logic and duration

### 4. TrafficLight
- **Fields:** currentState, direction
- **Methods:** setState(SignalState), getState(), getDirection(), handle(TrafficSignalController)

### 5. Intersection
- **Fields:** id, Map<Direction, TrafficLight> signals, Map<Direction, Map<String, Integer>> signalDurations, TrafficSignalController controller
- **Methods:** start(Direction), manualOverride(Direction), getSignal(Direction)

### 6. TrafficSignalController
- **Fields:** Map<Direction, TrafficLight> signals, Map<Direction, Map<String, Integer>> signalDurations, scheduler
- **Methods:** start(Direction), scheduleStateChange(...), getSignalDuration(...), getNextDirection(...), getTrafficLight(...), manualOverride(Direction)

---

## Design Patterns Used

- **State Pattern:** Each signal state (GREEN, YELLOW, RED) encapsulates its own behavior and transition logic.
- **Scheduler/Timer:** For handling timed transitions between states.
- **Strategy Pattern:** (Conceptually) for supporting different timing strategies per direction/state.

---

## Example Usage

```ts
// Configure durations per direction and state
const signalDurations = new Map<Direction, Map<string, number>>([
    [Direction.NORTH, new Map([["GREEN", 4], ["YELLOW", 2], ["RED", 3]])],
    [Direction.SOUTH, new Map([["GREEN", 3], ["YELLOW", 2], ["RED", 4]])],
    [Direction.EAST, new Map([["GREEN", 5], ["YELLOW", 2], ["RED", 3]])],
    [Direction.WEST, new Map([["GREEN", 2], ["YELLOW", 2], ["RED", 5]])]
]);

// Initialize traffic lights
const signals = new Map<Direction, TrafficLight>();
for (const direction of Object.values(Direction)) {
    signals.set(direction, new TrafficLight(direction));
}

// Create and start the controller
const intersection1 = new Intersection("1", signals, signalDurations);
intersection1.start(Direction.NORTH);
```

---

## Demo

See `TrafficSignalSystemDemo.ts` for a sample usage and simulation of the traffic signal system.

---

## Extending the Framework

- **Add new directions:** Add to the `Direction` enum and update configuration.
- **Add new states:** Add to the `SignalState` interface and implement new state classes.
- **Custom timing strategies:** Implement new strategies for special intersections or adaptive signals.

---