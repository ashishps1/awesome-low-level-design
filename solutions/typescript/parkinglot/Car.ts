import { carType } from "./types";

class Car {
  private carType: carType;
  private carNumber: string
  constructor(carType: carType, carNumber: string) {
    this.carType = carType;
    this.carNumber = carNumber
  }

  get getCar() {
    return {
      carType: this.carType,
      carNumber: this.carNumber
    };
  }
}

export default Car;
