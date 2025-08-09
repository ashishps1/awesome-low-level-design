import threading
from typing import Set
from direction import Direction
from request import Request
from elevator_state import ElevatorState, IdleState
from elevator_observer import ElevatorObserver
import time

class Elevator:
    def __init__(self, elevator_id: int):
        self.id = elevator_id
        self.current_floor = 1
        self.current_floor_lock = threading.Lock()
        self.state = IdleState()
        self.is_running = True
        
        self.up_requests = set()
        self.down_requests = set()
        
        # Observer Pattern: List of observers
        self.observers = []

    # --- Observer Pattern Methods ---
    def add_observer(self, observer: ElevatorObserver):
        self.observers.append(observer)
        observer.update(self)  # Send initial state

    def notify_observers(self):
        for observer in self.observers:
            observer.update(self)

    # --- State Pattern Methods ---
    def set_state(self, state: ElevatorState):
        self.state = state
        self.notify_observers()  # Notify observers on direction change

    def move(self):
        self.state.move(self)

    # --- Request Handling ---
    def add_request(self, request: Request):
        print(f"Elevator {self.id} processing: {request}")
        self.state.add_request(self, request)

    # --- Getters and Setters ---
    def get_id(self) -> int:
        return self.id

    def get_current_floor(self) -> int:
        with self.current_floor_lock:
            return self.current_floor

    def set_current_floor(self, floor: int):
        with self.current_floor_lock:
            self.current_floor = floor
        self.notify_observers()  # Notify observers on floor change

    def get_direction(self) -> Direction:
        return self.state.get_direction()

    def get_up_requests(self) -> Set[int]:
        return self.up_requests

    def get_down_requests(self) -> Set[int]:
        return self.down_requests

    def is_elevator_running(self) -> bool:
        return self.is_running

    def stop_elevator(self):
        self.is_running = False

    def run(self):
        while self.is_running:
            self.move()
            try:
                time.sleep(1)  # Simulate movement time
            except KeyboardInterrupt:
                self.is_running = False
                break