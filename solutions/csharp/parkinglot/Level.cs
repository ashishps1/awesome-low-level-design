using System;
using System.Collections.Generic;
using ParkingLot.VehicleTypes;

namespace ParkingLot
{
    public class Level
    {
        private readonly int floor;
        private readonly List<ParkingSpot> parkingSpots;

        public Level(int floor, int numSpots)
        {
            this.floor = floor;
            parkingSpots = new List<ParkingSpot>(numSpots);

            double spotsForBikes = 0.50;
            double spotsForCars = 0.40;

            int numBikes = (int)(numSpots * spotsForBikes);
            int numCars = (int)(numSpots * spotsForCars);

            for (int i = 1; i <= numBikes; i++)
            {
                parkingSpots.Add(new ParkingSpot(i, VehicleType.MOTORCYCLE));
            }
            for (int i = numBikes + 1; i <= numBikes + numCars; i++)
            {
                parkingSpots.Add(new ParkingSpot(i, VehicleType.CAR));
            }
            for (int i = numBikes + numCars + 1; i <= numSpots; i++)
            {
                parkingSpots.Add(new ParkingSpot(i, VehicleType.TRUCK));
            }
        }

        public bool ParkVehicle(Vehicle vehicle)
        {
            lock (parkingSpots)
            {
                foreach (var spot in parkingSpots)
                {
                    if (spot.IsAvailable() && spot.GetVehicleType() == vehicle.GetVehicleType())
                    {
                        spot.ParkVehicle(vehicle);
                        return true;
                    }
                }
            }
            return false;
        }

        public bool UnparkVehicle(Vehicle vehicle)
        {
            lock (parkingSpots)
            {
                foreach (var spot in parkingSpots)
                {
                    if (!spot.IsAvailable() && spot.GetParkedVehicle().Equals(vehicle))
                    {
                        spot.UnparkVehicle();
                        return true;
                    }
                }
            }
            return false;
        }

        public void DisplayAvailability()
        {
            Console.WriteLine($"Level {floor} Availability:");
            foreach (var spot in parkingSpots)
            {
                Console.WriteLine($"Spot {spot.GetSpotNumber()}: {(spot.IsAvailable() ? "Available For" : "Occupied By")} {spot.GetVehicleType()}");
            }
        }
    }
}