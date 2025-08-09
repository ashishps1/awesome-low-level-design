from direction import Direction
from traffic_light import TrafficLight
from intersection_state import IntersectionState, NorthSouthGreenState
from observer import TrafficObserver
from typing import Dict, List
import threading

class IntersectionController:
    def __init__(self, intersection_id: int, traffic_lights: Dict[Direction, TrafficLight], 
                 green_duration: int, yellow_duration: int):
        self._id = intersection_id
        self._traffic_lights = traffic_lights
        self._green_duration = green_duration
        self._yellow_duration = yellow_duration
        self._current_state = NorthSouthGreenState()  # Initial state for the intersection
        self._running = True

    def get_id(self) -> int:
        return self._id

    def get_green_duration(self) -> int:
        return self._green_duration

    def get_yellow_duration(self) -> int:
        return self._yellow_duration

    def get_light(self, direction: Direction) -> TrafficLight:
        return self._traffic_lights[direction]

    def set_state(self, state: IntersectionState):
        self._current_state = state

    def start(self):
        thread = threading.Thread(target=self.run)
        thread.start()

    def stop(self):
        self._running = False

    def run(self):
        while self._running:
            try:
                self._current_state.handle(self)
            except Exception as e:
                print(f"Intersection {self._id} encountered an error: {e}")
                self._running = False

    # Builder Pattern
    class Builder:
        def __init__(self, intersection_id: int):
            self._id = intersection_id
            self._green_duration = 5000  # default 5s
            self._yellow_duration = 2000  # default 2s
            self._observers: List[TrafficObserver] = []

        def with_durations(self, green: int, yellow: int) -> 'IntersectionController.Builder':
            self._green_duration = green
            self._yellow_duration = yellow
            return self

        def add_observer(self, observer: TrafficObserver) -> 'IntersectionController.Builder':
            self._observers.append(observer)
            return self

        def build(self) -> 'IntersectionController':
            lights = {}
            for direction in Direction:
                light = TrafficLight(self._id, direction)
                # Attach all registered observers to each light
                for observer in self._observers:
                    light.add_observer(observer)
                lights[direction] = light
            return IntersectionController(self._id, lights, self._green_duration, self._yellow_duration)
