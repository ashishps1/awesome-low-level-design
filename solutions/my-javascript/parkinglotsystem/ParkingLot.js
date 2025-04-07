export class ParkingLot {
    constructor() {
        this.instance = null;
        this.levels = [];
    }

    getInstance() {
        if (this.instance === null) {
            this.instance = new ParkingLot();
        }
        return this.instance;
    }

    addLevel(level) {
        this.levels.push(level);
    }

    // traverse to find available parking spot
    // park the vehicle in the first available spot
    parkVehicle(vehicle) {
        for (const level of this.levels) {
            const parkedSpot = level.parkVehicle(vehicle);
            if (parkedSpot) {
                console.log(`Vehicle parked in ${parkedSpot.spotNumber}`);
                return true;
            }
        }
        console.log(`No available parking spots for vehicle`);
        return false;
    }

    // traverse to find the vehicle
    // unpark the vehicle from the spot
    unParkVehicle(vehicle) {
        for (const level of this.levels) {
            if (level.unParkVehicle(vehicle)) {
                console.log(`Vehicle unparked from`)
                return true;
            }
        }
        console.log(`Vehicle not found`);
        return false;
    }

    displayAvailableSpots() {
        console.log(`Available parking spots:`);
        for (let i = 0; i < this.levels.length; i++) {
            this.levels[i].displayAvailableSpots();
        }
    }
}