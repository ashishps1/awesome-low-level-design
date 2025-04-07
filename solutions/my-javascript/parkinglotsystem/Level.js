import { ParkingSpot } from "./ParkingSpot.js";

export class Level {
  constructor(floor, spotsPerVehicleType) {
    this.floor = floor;
    this.parkingSpots = [];
    for (const vehicleType in spotsPerVehicleType) {
        for (let i = 0; i < spotsPerVehicleType[vehicleType]; i++) {
            this.parkingSpots.push(new ParkingSpot(`F${floor}${vehicleType[0]}${i}`, vehicleType));
        }
    }
  }

  parkVehicle(vehicle) {
    for (const parkingSpot of this.parkingSpots) {
      if (
        parkingSpot.isAvailable() &&
        parkingSpot.getVehicleType() === vehicle.getVehicleType()
      ) {
        return parkingSpot.parkVehicle(vehicle);
        // return true;
      }
    }
    return false;
  }

  unParkVehicle(vehicle) {
    for (const parkingSpot of this.parkingSpots) {
      if (!parkingSpot.isAvailable() && parkingSpot.getParkedVehicle() === vehicle) {
        parkingSpot.unParkVehicle();
        return true;
      }
    }
    return false;
  }

  displayAvailableSpots() {
    for (const spot of this.parkingSpots) {
      if (spot.isAvailable()) {
        console.log(`Parking spot ${spot.spotNumber} is available`);
      }
    }
  }
}
