type carType = "Car" | "Bike" | "Truck";

class ParkingLot {}

class ParkingLevel {}

class ParkingSpot {
  type: carType;
  parkedCar: Car | null;

  constructor(type: carType) {
    this.type = type;
  }

  parkCar(car: Car) {
    if (this.parkedCar) {
      throw new Error("This spot is already taken");
    }

    if (car.getCarType !== this.type) {
      throw new Error(`Spot is not supported for car ${car.getNumber}`);
    }
    return `Parked car ${car.getNumber}`;
  }

  unparkCar() {
    this.parkedCar = null;
  }
}

class Car {
  private number: string;
  private carType: carType;

  constructor(carNumber: string, carType: carType) {
    this.number = carNumber;
    this.carType = carType;
  }

  get getNumber() {
    return this.number;
  }

  get getCarType() {
    return this.carType;
  }
}
