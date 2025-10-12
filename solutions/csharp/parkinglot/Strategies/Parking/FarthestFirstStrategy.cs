class FarthestFirstStrategy : IParkingStrategy
{
    public ParkingSpot FindSpot(List<ParkingFloor> floors, Vehicle vehicle)
    {
        var reversedFloors = floors.AsEnumerable().Reverse().ToList();
        foreach (var floor in reversedFloors)
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