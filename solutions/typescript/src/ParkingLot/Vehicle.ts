import { carType } from "./types";

interface Vehicle {
  getNumber(): string;
  getType(): carType;
}


abstract class AbstractVehicle implements Vehicle {
  protected number: string;
  protected type: carType;

  constructor(number: string, type: carType) {
    this.number = number;
    this.type = type;
  }

  getNumber(): string {
    return this.number;
  }

  getType(): carType {
    return this.type;
  }
}

class Car extends AbstractVehicle {
  constructor(number: string) {
    super(number, "Car");
  }
}

class Bike extends AbstractVehicle {
  constructor(number: string) {
    super(number, "Bike");
  }
}

class Truck extends AbstractVehicle {
  constructor(number: string) {
    super(number, "Truck");
  }
}


export default AbstractVehicle
export {Car, Bike, Truck}