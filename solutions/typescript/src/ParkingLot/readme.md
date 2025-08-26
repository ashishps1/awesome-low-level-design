# Designing a Parking Lot System

## Requirements
1. The parking lot consists of multiple levels, and each level has a configurable number of parking spots.
2. The system must support various types of vehicles: Car, Motorcycle, and Truck.
3. Each parking spot supports a specific vehicle type.
4. The system should be able to:
5. Assign a parking spot to an incoming vehicle.
6. Free a spot when a vehicle exits.
7. Track and report spot availability in real time.
8. The system should support multiple entry and exit points with concurrent access handling (simulate multi-threading behavior where needed).
9. The design must showcase solid TypeScript OOP principles: classes, interfaces, abstract classes, and enums.


## Design Patterns Used:
1. Use TypeScript with classes, interfaces, and enums.
    * `Singleton`: Ensure only one instance of the ParkingLot exists.
    * `Factory(optional)`: For creating vehicles dynamically.
    * `Observer(optional)`: To notify users when a spot becomes available.
2. Ensure thread-safety where required using appropriate concurrency-safe constructs (e.g., Mutex simulation, Promise control).

3. Build a simple `Main.ts` file or script to demonstrate usage.