class CompletedState : ITripState
{
    public void Request(Trip trip)
    {
        Console.WriteLine("Cannot request a trip that is already completed.");
    }

    public void Assign(Trip trip, Driver driver)
    {
        Console.WriteLine("Cannot assign a driver to a completed trip.");
    }

    public void Start(Trip trip)
    {
        Console.WriteLine("Cannot start a completed trip.");
    }

    public void End(Trip trip)
    {
        Console.WriteLine("Trip is already completed.");
    }
}