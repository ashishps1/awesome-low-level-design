import { carType } from "./types";
import AbstractVehicle from "./Vehicle";

class ParkingSpot {
  spotName: string;
  protected type: carType;
  protected parkedCar: AbstractVehicle | null;

  constructor(spotName: string, type: carType) {
    this.spotName = spotName;
    this.type = type;
  }

  get isAvailable(): boolean {
    return !this.parkedCar;
  }

  canFit(car: AbstractVehicle): boolean {
    return car.getType() === this.type;
  }

  parkCar(car: AbstractVehicle): void {
    if (!this.isAvailable) {
      throw new Error("Spot already occupied.");
    }

    if (!this.canFit(car)) {
      throw new Error(`${car.getNumber()} can't fit in this spot.`);
    }

    this.parkedCar = car;
    console.log(`Parked car${car.getNumber()}.`);
  }

  unparkCar(): void {
    this.parkedCar = null;
  }

  getVehicle(): AbstractVehicle | null {
    return this.parkedCar;
  }

  get getSpotType(): carType {
    return this.type;
  }
}

export default ParkingSpot;
