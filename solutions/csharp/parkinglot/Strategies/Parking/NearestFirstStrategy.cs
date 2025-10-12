class NearestFirstStrategy : IParkingStrategy
{
    public ParkingSpot FindSpot(List<ParkingFloor> floors, Vehicle vehicle)
    {
        foreach (var floor in floors)
        {
            var spot = floor.FindAvailableSpot(vehicle);
            if (spot != null)
            {
                return spot;
            }
        }
        return null;
    }
}