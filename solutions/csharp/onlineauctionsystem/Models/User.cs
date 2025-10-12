class User : IAuctionObserver
{
    private readonly string id;
    private readonly string name;

    public User(string name)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
    }

    public string GetId()
    {
        return id;
    }

    public string GetName()
    {
        return name;
    }

    public void OnUpdate(Auction auction, string message)
    {
        Console.WriteLine($"--- Notification for {name} ---");
        Console.WriteLine($"Auction: {auction.GetItemName()}");
        Console.WriteLine($"Message: {message}");
        Console.WriteLine("---------------------------\n");
    }

    public override bool Equals(object obj)
    {
        if (this == obj) return true;
        if (obj == null || GetType() != obj.GetType()) return false;
        User user = (User)obj;
        return id.Equals(user.id);
    }

    public override int GetHashCode()
    {
        return id.GetHashCode();
    }
}