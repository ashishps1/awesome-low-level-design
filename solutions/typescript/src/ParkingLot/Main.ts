import ParkingLot from "./ParkingLot"
import ParkingFloor from "./Floor"
import ParkingSpot from "./Spot"
import { Car } from "./Vehicle"

const parkYourCar = ParkingLot.getInstance("ParkYourCar")
console.log(parkYourCar.name)

const car1 = new Car("car-1")
const car2 = new Car("car-2")
const car3 = new Car("car-3")
const car4 = new Car("car-4")

const a1 = new ParkingSpot('a-1', "Car")
// const a2 = new ParkingSpot('a-2', "Truck")
const a3 = new ParkingSpot('a-3', "Bike")
const a4 = new ParkingSpot('a-4', "Car")
// const a5 = new ParkingSpot('a-5', "Car")


const f1 = new ParkingFloor("1")
f1.addSpot(a1)
// f1.addSpot(a2)
f1.addSpot(a3)
f1.addSpot(a4)
// f1.addSpot(a5)

const b1 = new ParkingSpot('b-1', "Car")
const b2 = new ParkingSpot('b-2', "Truck")
// const b3 = new ParkingSpot('b-3', "Bike")
const b4 = new ParkingSpot('b-4', "Car")
// const b5 = new ParkingSpot('b-5', "Car")


const f2 = new ParkingFloor("2")
f2.addSpot(b1)
f2.addSpot(b2)
// f2.addSpot(b3)
f2.addSpot(b4)
// f2.addSpot(b5)

parkYourCar.addFloor(f1)
parkYourCar.addFloor(f2)
parkYourCar.spotAvailability()

parkYourCar.parkCar(car1)
parkYourCar.parkCar(car2)
parkYourCar.spotAvailability()