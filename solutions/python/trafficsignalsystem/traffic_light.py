from signal import Signal
from threading import Lock

class TrafficLight:
    def __init__(self, id: str, red_duration: int, yellow_duration: int, green_duration: int):
        self.id = id
        self.current_signal = Signal.RED
        self.red_duration = red_duration
        self.yellow_duration = yellow_duration
        self.green_duration = green_duration
        self.lock = Lock()

    def change_signal(self, new_signal: Signal):
        with self.lock:
            self.current_signal = new_signal
            self.notify_observers()

    def get_current_signal(self):
        return self.current_signal

    def notify_observers(self):
        # Notify observers (e.g., roads) about the signal change
        pass