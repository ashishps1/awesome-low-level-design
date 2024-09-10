import time
from threading import Lock, Condition
from request import Request
from direction import Direction


class Elevator:
    def __init__(self, id: int, capacity: int):
        self.id = id
        self.capacity = capacity
        self.current_floor = 1
        self.current_direction = Direction.UP
        self.requests = []
        self.lock = Lock()
        self.condition = Condition(self.lock)

    def add_request(self, request: Request):
        with self.lock:
            if len(self.requests) < self.capacity:
                self.requests.append(request)
                print(
                    f"Elevator {self.id} added request: {request.source_floor} to {request.destination_floor}"
                )
                self.condition.notify_all()

    def get_next_request(self) -> Request:
        with self.lock:
            while not self.requests:
                self.condition.wait()
            return self.requests.pop(0)

    def process_requests(self):
        while True:
            request = self.get_next_request()  # This will wait until there's a request
            self.process_request(request)

    def process_request(self, request: Request):
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
