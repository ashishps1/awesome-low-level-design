class DeliveryAgent : User
{
    private volatile bool isAvailable = true;
    private Address currentLocation;
    private readonly object locationLock = new object();

    public DeliveryAgent(string name, string phone, Address currentLocation) : base(name, phone)
    {
        this.currentLocation = currentLocation;
    }

    public void SetAvailable(bool available)
    {
        isAvailable = available;
    }

    public bool IsAvailableAgent()
    {
        return isAvailable;
    }

    public void SetCurrentLocation(Address currentLocation)
    {
        lock (locationLock)
        {
            this.currentLocation = currentLocation;
        }
    }

    public Address GetCurrentLocation()
    {
        lock (locationLock)
        {
            return currentLocation;
        }
    }

    public override void OnUpdate(Order order)
    {
        Console.WriteLine($"--- Notification for Delivery Agent {GetName()} ---");
        Console.WriteLine($"  Order {order.GetId()} update: Status is {order.GetStatus()}.");
        Console.WriteLine("-------------------------------------------\n");
    }
}