import threading
import time
from direction import Direction

class Elevator:
    def __init__(self, elevator_id, capacity):
        self.id = elevator_id
        self.capacity = capacity
        self.current_floor = 1
        self.current_direction = Direction.UP
        self.requests = []
        self.lock = threading.Lock()
        self.condition = threading.Condition(self.lock)

    def add_request(self, request):
        with self.lock:
            if len(self.requests) < self.capacity:
                self.requests.append(request)
                print(f"Elevator {self.id} added request: {request}")
                with self.condition:
                    self.condition.notify()

    def get_next_request(self):
        with self.lock:
            while not self.requests:
                with self.condition:
                    self.condition.wait()
            return self.requests.pop(0)

    def process_requests(self):
        while True:
            with self.lock:
                while not self.requests:
                    with self.condition:
                        self.condition.wait()
                request = self.get_next_request()
                self._process_request(request)

    def _process_request(self, request):
        start_floor = self.current_floor
        end_floor = request.destination_floor
        if start_floor < end_floor:
            self.current_direction = Direction.UP
            for i in range(start_floor, end_floor + 1):
                self.current_floor = i
                print(f"Elevator {self.id} reached floor {self.current_floor}")
                time.sleep(1)  # Simulating elevator movement
        elif start_floor > end_floor:
            self.current_direction = Direction.DOWN
            for i in range(start_floor, end_floor - 1, -1):
                self.current_floor = i
                print(f"Elevator {self.id} reached floor {self.current_floor}")
                time.sleep(1)  # Simulating elevator movement

    def run(self):
        self.process_requests()

    def get_current_floor(self):
        return self.current_floor