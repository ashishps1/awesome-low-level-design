from parking_lot import ParkingLot
from parking_floor import ParkingFloor
from parking_spot import ParkingSpot
from vehicle_size import VehicleSize
from fee_strategy import VehicleBasedFeeStrategy
from bike import Bike
from car import Car
from truck import Truck

class ParkingLotDemo:
    @staticmethod
    def main():
        parking_lot = ParkingLot.get_instance()

        # 1. Initialize the parking lot with floors and spots
        floor1 = ParkingFloor(1)
        floor1.add_spot(ParkingSpot("F1-S1", VehicleSize.SMALL))
        floor1.add_spot(ParkingSpot("F1-M1", VehicleSize.MEDIUM))
        floor1.add_spot(ParkingSpot("F1-L1", VehicleSize.LARGE))

        floor2 = ParkingFloor(2)
        floor2.add_spot(ParkingSpot("F2-M1", VehicleSize.MEDIUM))
        floor2.add_spot(ParkingSpot("F2-M2", VehicleSize.MEDIUM))

        parking_lot.add_floor(floor1)
        parking_lot.add_floor(floor2)

        parking_lot.set_fee_strategy(VehicleBasedFeeStrategy())

        # 2. Simulate vehicle entries
        print("\n--- Vehicle Entries ---")
        floor1.display_availability()
        floor2.display_availability()

        bike = Bike("B-123")
        car = Car("C-456")
        truck = Truck("T-789")

        bike_ticket = parking_lot.park_vehicle(bike)
        car_ticket = parking_lot.park_vehicle(car)
        truck_ticket = parking_lot.park_vehicle(truck)

        print("\n--- Availability after parking ---")
        floor1.display_availability()
        floor2.display_availability()

        # 3. Simulate another car entry (should go to floor 2)
        car2 = Car("C-999")
        car2_ticket = parking_lot.park_vehicle(car2)

        # 4. Simulate a vehicle entry that fails (no available spots)
        bike2 = Bike("B-000")
        failed_bike_ticket = parking_lot.park_vehicle(bike2)

        # 5. Simulate vehicle exits and fee calculation
        print("\n--- Vehicle Exits ---")

        if car_ticket is not None:
            fee = parking_lot.unpark_vehicle(car.get_license_number())
            if fee is not None:
                print(f"Car C-456 unparked. Fee: ${fee:.2f}")

        print("\n--- Availability after one car leaves ---")
        floor1.display_availability()
        floor2.display_availability()


if __name__ == "__main__":
    ParkingLotDemo.main()