from abc import ABC, abstractmethod
from direction import Direction
from request import Request
from request_source import RequestSource

class ElevatorState(ABC):
    @abstractmethod
    def move(self, elevator):
        pass

    @abstractmethod
    def add_request(self, elevator, request: Request):
        pass

    @abstractmethod
    def get_direction(self) -> Direction:
        pass

class IdleState(ElevatorState):
    def move(self, elevator):
        if elevator.get_up_requests():
            elevator.set_state(MovingUpState())
        elif elevator.get_down_requests():
            elevator.set_state(MovingDownState())
        # Else stay idle

    def add_request(self, elevator, request: Request):
        if request.target_floor > elevator.get_current_floor():
            elevator.get_up_requests().add(request.target_floor)
        elif request.target_floor < elevator.get_current_floor():
            elevator.get_down_requests().add(request.target_floor)
        # If request is for current floor, doors would open (handled implicitly by moving to that floor)

    def get_direction(self) -> Direction:
        return Direction.IDLE
    
class MovingUpState(ElevatorState):
    def move(self, elevator):
        if not elevator.get_up_requests():
            elevator.set_state(IdleState())
            return

        next_floor = min(elevator.get_up_requests())
        elevator.set_current_floor(elevator.get_current_floor() + 1)

        if elevator.get_current_floor() == next_floor:
            print(f"Elevator {elevator.get_id()} stopped at floor {next_floor}")
            elevator.get_up_requests().remove(next_floor)

        if not elevator.get_up_requests():
            elevator.set_state(IdleState())

    def add_request(self, elevator, request: Request):
        # Internal requests always get added to the appropriate queue
        if request.source == RequestSource.INTERNAL:
            if request.target_floor > elevator.get_current_floor():
                elevator.get_up_requests().add(request.target_floor)
            else:
                elevator.get_down_requests().add(request.target_floor)
            return

        # External requests
        if request.direction == Direction.UP and request.target_floor >= elevator.get_current_floor():
            elevator.get_up_requests().add(request.target_floor)
        elif request.direction == Direction.DOWN:
            elevator.get_down_requests().add(request.target_floor)

    def get_direction(self) -> Direction:
        return Direction.UP
    
class MovingDownState(ElevatorState):
    def move(self, elevator):
        if not elevator.get_down_requests():
            elevator.set_state(IdleState())
            return

        next_floor = max(elevator.get_down_requests())
        elevator.set_current_floor(elevator.get_current_floor() - 1)

        if elevator.get_current_floor() == next_floor:
            print(f"Elevator {elevator.get_id()} stopped at floor {next_floor}")
            elevator.get_down_requests().remove(next_floor)

        if not elevator.get_down_requests():
            elevator.set_state(IdleState())

    def add_request(self, elevator, request: Request):
        # Internal requests always get added to the appropriate queue
        if request.source == RequestSource.INTERNAL:
            if request.target_floor > elevator.get_current_floor():
                elevator.get_up_requests().add(request.target_floor)
            else:
                elevator.get_down_requests().add(request.target_floor)
            return

        # External requests
        if request.direction == Direction.DOWN and request.target_floor <= elevator.get_current_floor():
            elevator.get_down_requests().add(request.target_floor)
        elif request.direction == Direction.UP:
            elevator.get_up_requests().add(request.target_floor)

    def get_direction(self) -> Direction:
        return Direction.DOWN