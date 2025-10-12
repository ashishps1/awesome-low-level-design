interface IParkingStrategy
{
    ParkingSpot FindSpot(List<ParkingFloor> floors, Vehicle vehicle);
}