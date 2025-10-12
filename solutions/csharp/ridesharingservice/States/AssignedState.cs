class AssignedState : ITripState
{
    public void Request(Trip trip)
    {
        Console.WriteLine("Trip has already been requested and assigned.");
    }

    public void Assign(Trip trip, Driver driver)
    {
        Console.WriteLine("Trip is already assigned. To re-assign, cancel first.");
    }

    public void Start(Trip trip)
    {
        trip.SetStatus(TripStatus.IN_PROGRESS);
        trip.SetState(new InProgressState());
    }

    public void End(Trip trip)
    {
        Console.WriteLine("Cannot end a trip that has not started.");
    }
}