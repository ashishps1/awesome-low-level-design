class Rider : User
{
    public Rider(string name, string contact) : base(name, contact) { }

    public override void OnUpdate(Trip trip)
    {
        Console.WriteLine($"--- Notification for Rider {Name} ---");
        Console.WriteLine($"  Trip {trip.Id} is now {trip.Status}.");
        if (trip.Driver != null)
        {
            Console.WriteLine($"  Driver: {trip.Driver.Name} in a {trip.Driver.Vehicle.Model} ({trip.Driver.Vehicle.LicenseNumber})");
        }
        Console.WriteLine("--------------------------------\n");
    }
}