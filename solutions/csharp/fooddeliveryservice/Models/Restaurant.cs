class Restaurant : IOrderObserver
{
    private readonly string id;
    private readonly string name;
    private readonly Address address;
    private readonly Menu menu;

    public Restaurant(string name, Address address)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
        this.address = address;
        this.menu = new Menu();
    }

    public void AddToMenu(MenuItem item)
    {
        menu.AddItem(item);
    }

    public string GetId() { return id; }
    public string GetName() { return name; }
    public Address GetAddress() { return address; }
    public Menu GetMenu() { return menu; }

    public void OnUpdate(Order order)
    {
        Console.WriteLine($"--- Notification for Restaurant {GetName()} ---");
        Console.WriteLine($"  Order {order.GetId()} has been updated to {order.GetStatus()}.");
        Console.WriteLine("---------------------------------------\n");
    }
}