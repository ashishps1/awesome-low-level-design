from abc import ABC, abstractmethod
from direction import Direction
from light_color import LightColor

class TrafficObserver(ABC):
    @abstractmethod
    def update(self, intersection_id: int, direction: Direction, color: LightColor):
        pass

class CentralMonitor(TrafficObserver):
    def update(self, intersection_id: int, direction: Direction, color: LightColor):
        print(f"[MONITOR] Intersection {intersection_id}: Light for {direction.value} direction changed to {color.value}.")