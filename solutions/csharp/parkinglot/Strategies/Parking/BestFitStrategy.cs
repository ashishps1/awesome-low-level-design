class BestFitStrategy : IParkingStrategy
{
    public ParkingSpot FindSpot(List<ParkingFloor> floors, Vehicle vehicle)
    {
        ParkingSpot bestSpot = null;

        foreach (var floor in floors)
        {
            var spotOnThisFloor = floor.FindAvailableSpot(vehicle);

            if (spotOnThisFloor != null)
            {
                if (bestSpot == null)
                {
                    bestSpot = spotOnThisFloor;
                }
                else
                {
                    if ((int)spotOnThisFloor.GetSpotSize() < (int)bestSpot.GetSpotSize())
                    {
                        bestSpot = spotOnThisFloor;
                    }
                }
            }
        }
        return bestSpot;
    }
}