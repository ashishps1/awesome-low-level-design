namespace ParkingLot.VehicleTypes
{
    public class Car : Vehicle
    {
        public Car(string licensePlate) : base(licensePlate, VehicleType.CAR) { }
    }
}