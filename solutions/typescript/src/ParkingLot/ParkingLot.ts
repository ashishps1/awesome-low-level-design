import ParkingFloor from "./Floor";
import ParkingSpot from "./Spot";
import AbstractVehicle from "./Vehicle";

class ParkingLot {
  private static instance: ParkingLot;
  private floors: ParkingFloor[]
  name : string;
  protected carSpotMap: Record<string,ParkingSpot> 

  constructor(name: string){
    this.name = name
    this.floors = []
    this.carSpotMap = {}
  }

  static getInstance(name: string = "Default"): ParkingLot{
    if(!ParkingLot.instance){
      this.instance = new ParkingLot(name)
    }
    return ParkingLot.instance
  }

  parkCar(vehicle: AbstractVehicle): void{
    for(let floor of this.floors){
      const availableSpot = floor.findAvailableSpot(vehicle)
      if(availableSpot){
        availableSpot.parkCar(vehicle)
        console.log(`${vehicle.getNumber()} parked on ${availableSpot.spotName}`)
        return 
      }
    }
  }

  unparkCar(vehicle: AbstractVehicle){
    const spot = this.carSpotMap[vehicle.getNumber()] 
    if(!spot){
      throw new Error(`${vehicle.getNumber()} is not Parked.`)
    }
    spot.unparkCar()
    delete this.carSpotMap[vehicle.getNumber()];
  }

  spotAvailability(){
    for(let floor of this.floors){
      const availability = floor.reportAvailability()
      console.log(`${floor.floor} : `, availability)
    }
  }

  addFloor(floor : ParkingFloor){
    this.floors.push(floor)
  }
}

export default ParkingLot