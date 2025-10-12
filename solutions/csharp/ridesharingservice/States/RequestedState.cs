class RequestedState : ITripState
{
    public void Request(Trip trip)
    {
        Console.WriteLine("Trip is already in requested state.");
    }

    public void Assign(Trip trip, Driver driver)
    {
        trip.SetDriver(driver);
        trip.SetStatus(TripStatus.ASSIGNED);
        trip.SetState(new AssignedState());
    }

    public void Start(Trip trip)
    {
        Console.WriteLine("Cannot start a trip that has not been assigned a driver.");
    }

    public void End(Trip trip)
    {
        Console.WriteLine("Cannot end a trip that has not been assigned a driver.");
    }
}