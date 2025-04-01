namespace ParkingLot.VehicleTypes
{
    public abstract class Vehicle
    {
        protected string licensePlate;
        protected VehicleType type;

        public Vehicle(string licensePlate, VehicleType type)
        {
            this.licensePlate = licensePlate;
            this.type = type;
        }

        public VehicleType GetVehicleType()
        {
            return type;
        }
    }
}