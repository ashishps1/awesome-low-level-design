from direction import Direction
from light_color import LightColor
from signal_state import SignalState
from observer import TrafficObserver
from typing import List
from signal_state import RedState, GreenState

class TrafficLight:
    def __init__(self, intersection_id: int, direction: Direction):
        self._intersection_id = intersection_id
        self._direction = direction
        self._current_color = None
        self._current_state = RedState()  # Default state is Red
        self._next_state = None
        self._observers: List[TrafficObserver] = []
        self._current_state.handle(self)

    # This is called by the IntersectionController to initiate a G-Y-R cycle
    def start_green(self):
        self._current_state = GreenState()
        self._current_state.handle(self)

    # This is called by the IntersectionController to transition from G->Y or Y->R
    def transition(self):
        self._current_state = self._next_state
        self._current_state.handle(self)

    def set_color(self, color: LightColor):
        if self._current_color != color:
            self._current_color = color
            self._notify_observers()

    def set_next_state(self, state: SignalState):
        self._next_state = state

    def get_current_color(self) -> LightColor:
        return self._current_color

    def get_direction(self) -> Direction:
        return self._direction

    # Observer pattern methods
    def add_observer(self, observer: TrafficObserver):
        self._observers.append(observer)

    def remove_observer(self, observer: TrafficObserver):
        if observer in self._observers:
            self._observers.remove(observer)

    def _notify_observers(self):
        for observer in self._observers:
            observer.update(self._intersection_id, self._direction, self._current_color)