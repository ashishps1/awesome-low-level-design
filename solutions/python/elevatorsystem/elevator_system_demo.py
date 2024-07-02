import time
from elevator_controller import ElevatorController

class ElevatorSystemDemo:
    @staticmethod
    def run():
        controller = ElevatorController(3, 5)
        controller.request_elevator(5, 10)
        controller.request_elevator(3, 7)
        controller.request_elevator(8, 2)
        controller.request_elevator(1, 9)

        # Keep the main thread running
        try:
            while True:
                time.sleep(1)
        except KeyboardInterrupt:
            print("Elevator system stopped.")        

if __name__ == "__main__":
    ElevatorSystemDemo.run()