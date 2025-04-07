import { Level } from "./Level.js";
import { ParkingLot } from "./ParkingLot.js";
import { Car, Motorcycle, Truck } from "./Vehicle.js";
import { VehicleType } from "./VehicleType.js";

export class Demo {
    constructor() {
    }

    run() {
        console.log("Parking Lot System Demo");
        // Create parking lot instance
        const parkingLot = new ParkingLot().getInstance();
        parkingLot.addLevel(new Level(1, {[VehicleType.CAR]: 10, [VehicleType.MOTORCYCLE]: 5, [VehicleType.TRUCK]: 2}));
        parkingLot.addLevel(new Level(2, {[VehicleType.CAR]: 10, [VehicleType.MOTORCYCLE]: 5, [VehicleType.TRUCK]: 2}));

        const car = new Car("ABC123");
        const motorcycle = new Motorcycle("XYZ789");
        const truck = new Truck("LMN456");

        // Park vehicles
        parkingLot.parkVehicle(car);
        parkingLot.parkVehicle(motorcycle);
        parkingLot.parkVehicle(truck);

        // Unpark vehicles
        parkingLot.unParkVehicle(car);

        // Display available spots
        parkingLot.displayAvailableSpots();
    }
}

const demo = new Demo();
demo.run();