import { level } from "./types";

class ParkingLot {
  private levels: level[];

  constructor() {}

  addParkingLot(level: level) {
    this.levels.push(level);
  }

  getLevel(floor: number) {
    if (this.levels.length < floor) {
      return this.levels[floor];
    } else {
      throw new Error("Floor is not valid.");
    }
  }
}
