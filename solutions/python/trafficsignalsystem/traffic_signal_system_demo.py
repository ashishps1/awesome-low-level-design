from traffic_controller import TrafficController
from road import Road
from traffic_light import TrafficLight

class TrafficSignalSystemDemo:
    @staticmethod
    def run():
        traffic_controller = TrafficController.get_instance()

        # Create roads
        road1 = Road("R1", "Main Street")
        road2 = Road("R2", "Broadway")
        road3 = Road("R3", "Park Avenue")
        road4 = Road("R4", "Elm Street")

        # Create traffic lights
        traffic_light1 = TrafficLight("TL1", 30000, 5000, 60000)
        traffic_light2 = TrafficLight("TL2", 30000, 5000, 60000)
        traffic_light3 = TrafficLight("TL3", 30000, 5000, 60000)
        traffic_light4 = TrafficLight("TL4", 30000, 5000, 60000)

        # Assign traffic lights to roads
        road1.set_traffic_light(traffic_light1)
        road2.set_traffic_light(traffic_light2)
        road3.set_traffic_light(traffic_light3)
        road4.set_traffic_light(traffic_light4)

        # Add roads to the traffic controller
        traffic_controller.add_road(road1)
        traffic_controller.add_road(road2)
        traffic_controller.add_road(road3)
        traffic_controller.add_road(road4)

        # Start traffic control
        traffic_controller.start_traffic_control()

        # Simulate an emergency on a specific road
        traffic_controller.handle_emergency("R2")


if __name__ == "__main__":
    TrafficSignalSystemDemo.run()