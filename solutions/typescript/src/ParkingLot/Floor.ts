import ParkingSpot from "./Spot";
import { carType } from "./types";
import AbstractVehicle from "./Vehicle";

type carWiseSpot = Record<carType, ParkingSpot[]>


class ParkingFloor {
  floor: string;
  spots: ParkingSpot[];

  constructor(floor: string) {
    this.floor = floor
    this.spots = []
  }

  addSpot(spot: ParkingSpot) {
    this.spots.push(spot)
  }

  reportAvailability(): carWiseSpot {
    const carWiseSpots: carWiseSpot = {
      "Car": [],
      "Truck": [],
      "Bike": []
    }

    for (let spot of this.spots) {
      if (spot.isAvailable) {
        carWiseSpots[spot.getSpotType].push(spot)
      }
    }
    return carWiseSpots
  }

  findAvailableSpot(vehicle: AbstractVehicle): ParkingSpot | null {
    for (let spot of this.spots) {
      if (spot.canFit(vehicle) && spot.isAvailable) {
        return spot
      }
    }
    return null
  }
}

export default ParkingFloor