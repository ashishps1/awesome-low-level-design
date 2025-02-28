using ParkingLot.VehicleTypes;

namespace ParkingLot
{
    public class ParkingLotDemo
    {
        public static void Run()
        {
            ParkingLot parkingLot = ParkingLot.GetInstance();
            parkingLot.AddLevel(new Level(1, 100));
            parkingLot.AddLevel(new Level(2, 80));

            Vehicle car = new Car("ABC123");
            Vehicle truck = new Truck("XYZ789");
            Vehicle motorcycle = new Motorcycle("M1234");

            // Park vehicles
            parkingLot.ParkVehicle(car);
            parkingLot.ParkVehicle(truck);
            parkingLot.ParkVehicle(motorcycle);

            // Display availability
            parkingLot.DisplayAvailability();

            // Unpark vehicle
            parkingLot.UnparkVehicle(motorcycle);

            // Display updated availability
            parkingLot.DisplayAvailability();
        }
    }
}