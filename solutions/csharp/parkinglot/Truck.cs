namespace ParkingLot.VehicleTypes
{
    public class Truck : Vehicle
    {
        public Truck(string licensePlate) : base(licensePlate, VehicleType.TRUCK) { }
    }
}