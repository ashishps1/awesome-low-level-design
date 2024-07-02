from signal import Signal

class TrafficLight:
    def __init__(self, light_id, red_duration, yellow_duration, green_duration):
        self.id = light_id
        self.current_signal = Signal.RED
        self.red_duration = red_duration
        self.yellow_duration = yellow_duration
        self.green_duration = green_duration

    def change_signal(self, new_signal):
        self.current_signal = new_signal
        self._notify_observers()

    def get_current_signal(self):
        return self.current_signal

    def get_red_duration(self):
        return self.red_duration

    def set_red_duration(self, red_duration):
        self.red_duration = red_duration

    def get_yellow_duration(self):
        return self.yellow_duration

    def set_yellow_duration(self, yellow_duration):
        self.yellow_duration = yellow_duration

    def get_green_duration(self):
        return self.green_duration

    def set_green_duration(self, green_duration):
        self.green_duration = green_duration

    def _notify_observers(self):
        # Notify observers (e.g., roads) about the signal change
        # ...
        pass