import time
from traffic_control_system import TrafficControlSystem

class TrafficSystemDemo:
    @staticmethod
    def main():
        # 1. Get the singleton TrafficControlSystem instance
        system = TrafficControlSystem.get_instance()

        # 2. Add intersections to the system
        system.add_intersection(1, 500, 200)
        system.add_intersection(2, 700, 150)

        # 3. Start the system
        system.start_system()

        # 4. Let the simulation run for a while (e.g., 5 seconds)
        try:
            time.sleep(5)
        except KeyboardInterrupt:
            pass

        # 5. Stop the system gracefully
        system.stop_system()

if __name__ == "__main__":
    TrafficSystemDemo.main()