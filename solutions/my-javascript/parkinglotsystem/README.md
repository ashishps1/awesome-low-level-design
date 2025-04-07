# Designing a Parking Lot System

## Requirements
1. multiple levels, each with number of spots
2. system should be able to assign parking space to vehicle upon entry
3. system should be able to release parking space when vehicle leaves
4. system should be able to track availability of parking spots

5. system should be able to handle multiple entry/exit at once
6. system should be able to support different vehicles (cars, motorcycles, trucks) - different parking spots for each

## Entities
1. **Demo** Class - demonstrate usuage of parking lot system
2. **ParkingLot** Class - singleton, where client side requests are processed. has multiple levels
3. **Levels** Class - have multiple spots
4. **ParkingSpot** Class - car type, availability
5. **Vehicle** Class - abstract for car, motocycle, truck
6. **VehicleType** Enum

## Function Flow
1. parkingLot.parkVehicle -> traverse through levels and ask level.parkVehicle -> traverse through parking spots in that level and ask parkingSpot.parkVehicle -> parkingSpot ask itself if it can park the vehicle and returns the answer back up the stack