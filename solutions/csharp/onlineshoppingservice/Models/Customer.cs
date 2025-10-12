class Customer : IOrderObserver
{
    private readonly string id;
    private readonly string name;
    private readonly string email;
    private readonly Account account;
    private Address shippingAddress;

    public Customer(string name, string email, string password, Address shippingAddress)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
        this.email = email;
        this.account = new Account(email, password);
        this.shippingAddress = shippingAddress;
    }

    public void Update(Order order)
    {
        Console.WriteLine($"[Notification for {name}]: Your order #{order.GetId()} status has been updated to: {order.GetStatus()}.");
    }

    public string GetId() { return id; }
    public string GetName() { return name; }
    public Account GetAccount() { return account; }
    public Address GetShippingAddress() { return shippingAddress; }
    public void SetShippingAddress(Address address) { shippingAddress = address; }
}