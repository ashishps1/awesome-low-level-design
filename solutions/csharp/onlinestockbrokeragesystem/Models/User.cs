class User : IStockObserver
{
    private readonly string userId;
    private readonly string name;
    private readonly Account account;

    public User(string name, double initialCash)
    {
        this.userId = Guid.NewGuid().ToString();
        this.name = name;
        this.account = new Account(initialCash);
    }

    public string GetUserId() { return userId; }
    public string GetName() { return name; }
    public Account GetAccount() { return account; }

    public void Update(Stock stock)
    {
        Console.WriteLine($"[Notification for {name}] Stock {stock.GetSymbol()} price updated to: ${stock.GetPrice():F2}");
    }

    public void OrderStatusUpdate(Order order)
    {
        Console.WriteLine($"[Order Notification for {name}] Order {order.GetOrderId()} for {order.GetStock().GetSymbol()} is now {order.GetStatus()}.");
    }
}