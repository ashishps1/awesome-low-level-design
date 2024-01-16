# Designing a Traffic Signal Control System

In this article, we will explore the object-oriented design and implementation of a Traffic Signal Control System using Java. 

This system is crucial for managing traffic flow and ensuring safety at intersections.

## System Requirements

The Traffic Signal Control System should:

1. **Signal Timing Management**: Control the timing of traffic lights.
2. **Intersection Management**: Manage multiple traffic signals at an intersection.
3. **Mode Configuration**: Support different traffic modes.
4. **Emergency Override**: Allow manual control in emergencies.

## Core Use Cases

1. **Switching Signals**: Change signals from red to green and vice versa.
2. **Timing Adjustment**: Modify the duration of each signal.
3. **Mode Selection**: Choose operational modes.
4. **Emergency Control**: Manual override for emergencies.

## Key Classes:
- `TrafficSignalSystem`: Manages the system.
- `TrafficLight`: Represents an individual traffic light.
- `IntersectionController`: Manages lights at an intersection.
- `ControlPanel`: For manual control and emergency overrides.

## Java Implementation

### TrafficLight Class

Represents an individual traffic light.

```java
public class TrafficLight {
    private String id;
    private LightState state;

    public TrafficLight(String id) {
        this.id = id;
        this.state = LightState.RED;
    }

    public void changeState(LightState state) {
        this.state = state;
    }

    // Getters and setters...
}

enum LightState {
    RED, GREEN, YELLOW
}
```

### IntersectionController Class
Manages traffic lights at an intersection.

```java
import java.util.HashMap;
import java.util.Map;

public class IntersectionController {
    private Map<String, TrafficLight> trafficLights;

    public IntersectionController() {
        this.trafficLights = new HashMap<>();
    }

    public void addTrafficLight(TrafficLight light) {
        trafficLights.put(light.getId(), light);
    }

    public void changeSignal(String lightId, LightState state) {
        if (trafficLights.containsKey(lightId)) {
            trafficLights.get(lightId).changeState(state);
        }
    }

    // Additional methods...
}
```
### ControlPanel Class
For manual control and emergencies.

```java
public class ControlPanel {
    private IntersectionController controller;

    public ControlPanel(IntersectionController controller) {
        this.controller = controller;
    }

    public void overrideSignal(String lightId, LightState state) {
        controller.changeSignal(lightId, state);
    }

    // Additional methods...
}
```

### TrafficSignalSystem Class
Main class managing the traffic signal system.

```java
import java.util.ArrayList;
import java.util.List;

public class TrafficSignalSystem {
    private List<IntersectionController> intersectionControllers;

    public TrafficSignalSystem() {
        this.intersectionControllers = new ArrayList<>();
    }

    public void addIntersectionController(IntersectionController controller) {
        intersectionControllers.add(controller);
    }

    // Methods to update system configurations...
}
```
