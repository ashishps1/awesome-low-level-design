class Customer : User
{
    private readonly Address address;
    private readonly List<Order> orderHistory = new List<Order>();

    public Customer(string name, string phone, Address address) : base(name, phone)
    {
        this.address = address;
    }

    public void AddOrderToHistory(Order order)
    {
        orderHistory.Add(order);
    }

    public Address GetAddress()
    {
        return address;
    }

    public override void OnUpdate(Order order)
    {
        Console.WriteLine($"--- Notification for Customer {GetName()} ---");
        Console.WriteLine($"  Order {order.GetId()} is now {order.GetStatus()}.");
        Console.WriteLine("-------------------------------------\n");
    }
}