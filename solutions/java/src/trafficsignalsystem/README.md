# Traffic Signal System (LLD)

## Problem Statement

Design and implement a Traffic Signal System to manage the traffic lights at an intersection. The system should support configurable signal durations for each direction and state, automatic cycling of signals, and the ability to override signals as needed.

---

## Requirements

- **Multiple Directions:** The intersection supports multiple directions (e.g., NORTH, SOUTH, EAST, WEST).
- **Traffic Light States:** Each direction has a traffic light with states: GREEN, YELLOW, RED.
- **Configurable Durations:** Each direction and state can have its own configurable duration.
- **Automatic Cycling:** The system automatically cycles through the states for each direction in a round-robin fashion.
- **Override Capability:** The controller can override the current signal to set a specific direction to GREEN.
- **Extensibility:** Easy to add new directions or states if needed.

---

## Core Entities

- **Direction:** Enum representing the directions at the intersection (NORTH, SOUTH, EAST, WEST).
- **SignalState:** Enum representing the state of a traffic light (GREEN, YELLOW, RED).
- **TrafficLight:** Represents a traffic light for a direction, maintains its current state.
- **Intersection:** Represents the intersection, holds all traffic lights and their configurations.
- **TrafficSignalController:** Controls the cycling and overriding of traffic signals, manages timing and transitions.

---

## Class Design

### 1. Direction
- Enum: NORTH, SOUTH, EAST, WEST

### 2. SignalState
- Enum: GREEN, YELLOW, RED

### 3. TrafficLight
- **Fields:** currentState, direction
- **Methods:** changeSignal(SignalState), getState(), getDirection()

### 4. Intersection
- **Fields:** id, Map<Direction, TrafficLight> signals, Map<Direction, Map<SignalState, Integer>> signalDurations
- **Methods:** start(), getTrafficLight(Direction), etc.

### 5. TrafficSignalController
- **Fields:** Map<Direction, TrafficLight> signals, Map<Direction, Map<SignalState, Integer>> signalDurations, scheduler
- **Methods:** start(), override(Direction), rotateSignal(Direction, SignalState), getNextDirection(Direction)

---

## Design Patterns Used

- **State Pattern:** For managing the state transitions of each traffic light.
- **Scheduler/Timer:** For handling timed transitions between states.
- **Strategy Pattern:** (Conceptually) for supporting different timing strategies per direction/state.

---

## Example Usage

```java
// Configure signal durations per direction and state
Map<Direction, Map<SignalState, Integer>> signalDurations = new EnumMap<>(Direction.class);
signalDurations.put(Direction.NORTH, Map.of(
    SignalState.GREEN, 4,
    SignalState.YELLOW, 2,
    SignalState.RED, 3
));
// ... repeat for other directions

// Initialize traffic lights
Map<Direction, TrafficLight> signals = new EnumMap<>(Direction.class);
for (Direction direction : Direction.values()) {
    signals.put(direction, new TrafficLight(direction));
}

// Create and start the controller
TrafficSignalController controller = new TrafficSignalController(signals, signalDurations);
controller.start();
```

---

## Demo

See `TrafficSignalSystemDemo.java` for a sample usage and simulation of the traffic signal system.

---

## Extending the Framework

- **Add new directions:** Add to the `Direction` enum and update configuration.
- **Add new states:** Add to the `SignalState` enum and update logic in the controller.
- **Custom timing strategies:** Implement new strategies for special intersections or adaptive signals.

---