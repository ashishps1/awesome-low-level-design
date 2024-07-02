import threading
import time
from signal import Signal

class TrafficController:
    _instance = None

    def __init__(self):
        self.roads = {}

    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

    def add_road(self, road):
        self.roads[road.get_id()] = road

    def remove_road(self, road_id):
        del self.roads[road_id]

    def start_traffic_control(self):
        for road in self.roads.values():
            traffic_light = road.get_traffic_light()
            threading.Thread(target=self._control_traffic_light, args=(traffic_light,)).start()

    def _control_traffic_light(self, traffic_light):
        while True:
            try:
                time.sleep(traffic_light.get_red_duration() / 1000)
                traffic_light.change_signal(Signal.GREEN)
                time.sleep(traffic_light.get_green_duration() / 1000)
                traffic_light.change_signal(Signal.YELLOW)
                time.sleep(traffic_light.get_yellow_duration() / 1000)
                traffic_light.change_signal(Signal.RED)
            except InterruptedException:
                pass

    def handle_emergency(self, road_id):
        road = self.roads.get(road_id)
        if road:
            traffic_light = road.get_traffic_light()
            traffic_light.change_signal(Signal.GREEN)
            # Perform emergency handling logic
            # ...