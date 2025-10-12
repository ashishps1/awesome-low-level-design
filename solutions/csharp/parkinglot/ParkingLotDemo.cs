using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

public class ParkingLotDemo
{
    public static void Main()
    {
        var parkingLot = ParkingLot.GetInstance();

        // 1. Initialize the parking lot with floors and spots
        var floor1 = new ParkingFloor(1);
        floor1.AddSpot(new ParkingSpot("F1-S1", VehicleSize.SMALL));
        floor1.AddSpot(new ParkingSpot("F1-M1", VehicleSize.MEDIUM));
        floor1.AddSpot(new ParkingSpot("F1-L1", VehicleSize.LARGE));

        var floor2 = new ParkingFloor(2);
        floor2.AddSpot(new ParkingSpot("F2-M1", VehicleSize.MEDIUM));
        floor2.AddSpot(new ParkingSpot("F2-M2", VehicleSize.MEDIUM));

        parkingLot.AddFloor(floor1);
        parkingLot.AddFloor(floor2);

        parkingLot.SetFeeStrategy(new VehicleBasedFeeStrategy());

        // 2. Simulate vehicle entries
        Console.WriteLine("\n--- Vehicle Entries ---");
        floor1.DisplayAvailability();
        floor2.DisplayAvailability();

        var bike = new Bike("B-123");
        var car = new Car("C-456");
        var truck = new Truck("T-789");

        var bikeTicket = parkingLot.ParkVehicle(bike);
        var carTicket = parkingLot.ParkVehicle(car);
        var truckTicket = parkingLot.ParkVehicle(truck);

        Console.WriteLine("\n--- Availability after parking ---");
        floor1.DisplayAvailability();
        floor2.DisplayAvailability();

        // 3. Simulate another car entry (should go to floor 2)
        var car2 = new Car("C-999");
        var car2Ticket = parkingLot.ParkVehicle(car2);

        // 4. Simulate a vehicle entry that fails (no available spots)
        var bike2 = new Bike("B-000");
        var failedBikeTicket = parkingLot.ParkVehicle(bike2);

        // 5. Simulate vehicle exits and fee calculation
        Console.WriteLine("\n--- Vehicle Exits ---");

        if (carTicket != null)
        {
            var fee = parkingLot.UnparkVehicle(car.GetLicenseNumber());
            if (fee.HasValue)
            {
                Console.WriteLine($"Car C-456 unparked. Fee: ${fee.Value:F2}");
            }
        }

        Console.WriteLine("\n--- Availability after one car leaves ---");
        floor1.DisplayAvailability();
        floor2.DisplayAvailability();
    }
}