from abc import ABC, abstractmethod

class ElevatorObserver(ABC):
    @abstractmethod
    def update(self, elevator):
        pass

class Display(ElevatorObserver):
    def update(self, elevator):
        print(f"[DISPLAY] Elevator {elevator.get_id()} | Current Floor: {elevator.get_current_floor()} | Direction: {elevator.get_direction().value}")