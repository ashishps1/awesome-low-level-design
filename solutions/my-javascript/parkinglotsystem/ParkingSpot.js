export class ParkingSpot {
  // takes in a VehicleType enum value
  constructor(spotNumber, vehicleType) {
    this.spotNumber = spotNumber;
    this.available = true;
    this.vehicleType = vehicleType;
    this.parkedVehicle = null;
  }

  isAvailable() {
    return this.available;
  }

  getVehicleType() {
    return this.vehicleType;
  }

  parkVehicle(vehicle) {
    if (this.available && vehicle.getVehicleType() === this.vehicleType) {
      this.available = false;
      this.parkedVehicle = vehicle;
      return this
    } else {
      throw new Error("Invalid vehicle type or spot already occupied.");
    }
  }

  getParkedVehicle() {
    return this.parkedVehicle;
  }
  unParkVehicle() {
    this.available = true;
    this.parkedVehicle = null;
  }
}
