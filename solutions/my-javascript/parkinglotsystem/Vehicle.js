import { VehicleType } from "./VehicleType.js";

export class Vehicle {
    constructor(licensePlate, vehicleType) {
        // JS way of enforcing abstract classes
        if (new.target === Vehicle) {
            throw new TypeError("Cannot construct Vehicle instances directly");
        }
        this.licensePlate = licensePlate;
        this.vehicleType = vehicleType;
    }

    getVehicleType() {
        return this.vehicleType;
    }
}

export class Car extends Vehicle {
    constructor(licensePlate) {
        super(licensePlate, VehicleType.CAR);
    }
}

export class Motorcycle extends Vehicle {
    constructor(licensePlate) {
        super(licensePlate, VehicleType.MOTORCYCLE);
    }
}

export class Truck extends Vehicle {
    constructor(licensePlate) {
        super(licensePlate, VehicleType.TRUCK);
    }
}