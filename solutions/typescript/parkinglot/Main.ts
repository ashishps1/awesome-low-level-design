type carType = "Car" | "Bike" | "Truck";

class ParkingLot {
  name: string;
  parkingFloors: ParkingFloor[]

  constructor(name: string){
    this.name = name
  }

  addFloor(parkingFloor : ParkingFloor){
    this.parkingFloors.push(parkingFloor)
  }

  parkCar(car: Car){
    for(let parkingFloor of this.parkingFloors){
      if(parkingFloor.checkEmptySpot(car)){

      }
    }

  }
}

class ParkingFloor {
  floor: number
  parkingSpots : ParkingSpot[]

  constructor(floor: number){
    this.floor = floor
  }

  addSpot(parkingSpot: ParkingSpot){
    this.parkingSpots.push(parkingSpot)
  }

  parkCar(car: Car){
    for(let parkingSpot of this.parkingSpots){
      if(parkingSpot.isEmpty(car)){
        return true
      }
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

  get isAvailable(){
    
  }

  isEmpty(car: Car){
    if(!this.parkedCar && car.carType === this.type){
      return true
    }
    return false
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
