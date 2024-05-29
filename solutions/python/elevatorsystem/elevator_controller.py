from elevator import Elevator
import threading
from request import Request

class ElevatorController:
    def __init__(self, num_elevators, capacity):
        self.elevators = []
        for i in range(num_elevators):
            elevator = Elevator(i + 1, capacity)
            self.elevators.append(elevator)
            threading.Thread(target=elevator.run).start()

    def request_elevator(self, source_floor, destination_floor):
        optimal_elevator = self._find_optimal_elevator(source_floor, destination_floor)
        optimal_elevator.add_request(Request(source_floor, destination_floor))

    def _find_optimal_elevator(self, source_floor, destination_floor):
        optimal_elevator = None
        min_distance = float('inf')
        for elevator in self.elevators:
            distance = abs(source_floor - elevator.get_current_floor())
            if distance < min_distance:
                min_distance = distance
                optimal_elevator = elevator
        return optimal_elevator