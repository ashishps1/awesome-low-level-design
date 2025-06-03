type carType = "Car" | "Bike" | "Truck";

class ParkingLot {
  name: string;
  parkingFloors: ParkingFloor[];

  constructor(name: string) {
    this.name = name;
  }

  addFloor(parkingFloor: ParkingFloor) {
    this.parkingFloors.push(parkingFloor);
  }

  parkCar(car: Car) {
    for (let parkingFloor of this.parkingFloors) {
      const parkingSpot = parkingFloor.checkEmptySpot(car);
      if (parkingSpot) {
        parkingSpot.parkCar(car);
        return;
      }
    }
  }
}

class ParkingFloor {
  floor: number;
  parkingSpots: ParkingSpot[];

  constructor(floor: number) {
    this.floor = floor;
  }

  addSpot(parkingSpot: ParkingSpot) {
    this.parkingSpots.push(parkingSpot);
  }

  checkEmptySpot(car: Car) {
    for (let parkingSpot of this.parkingSpots) {
      if (parkingSpot.isAvailable && parkingSpot.canfit(car))
        return parkingSpot;
    }
  }


}

class ParkingSpot {
  type: carType;
  parkedCar: Car | null;

  constructor(type: carType) {
    this.type = type;
  }

  parkCar(car: Car) {
    if (!this.isAvailable) {
      throw new Error("This spot is already taken");
    }
    if (!this.canfit(car)) {
      throw new Error(`Spot is not supported for car ${car.getNumber}`);
    }
    this.parkedCar = car;
    console.log(`Parked car ${car.getNumber}`);
  }

  unparkCar() {
    this.parkedCar = null;
  }

  get isAvailable() {
    return !this.parkedCar;
  }

  canfit(car: Car) {
    return car.getCarType === this.type;
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
