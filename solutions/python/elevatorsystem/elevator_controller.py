from threading import Thread
from elevator import Elevator
from request import Request

class ElevatorController:
    def __init__(self, num_elevators: int, capacity: int):
        self.elevators = []
        for i in range(num_elevators):
            elevator = Elevator(i + 1, capacity)
            self.elevators.append(elevator)
            Thread(target=elevator.run).start()

    def request_elevator(self, source_floor: int, destination_floor: int):
        optimal_elevator = self.find_optimal_elevator(source_floor, destination_floor)
        optimal_elevator.add_request(Request(source_floor, destination_floor))

    def find_optimal_elevator(self, source_floor: int, destination_floor: int) -> Elevator:
        optimal_elevator = None
        min_distance = float('inf')

        for elevator in self.elevators:
            distance = abs(source_floor - elevator.current_floor)
            if distance < min_distance:
                min_distance = distance
                optimal_elevator = elevator

        return optimal_elevator