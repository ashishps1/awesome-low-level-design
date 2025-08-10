class InProgressState : ITripState
{
    public void Request(Trip trip)
    {
        Console.WriteLine("Trip is already in progress.");
    }

    public void Assign(Trip trip, Driver driver)
    {
        Console.WriteLine("Cannot assign a new driver while trip is in progress.");
    }

    public void Start(Trip trip)
    {
        Console.WriteLine("Trip is already in progress.");
    }

    public void End(Trip trip)
    {
        trip.SetStatus(TripStatus.COMPLETED);
        trip.SetState(new CompletedState());
    }
}