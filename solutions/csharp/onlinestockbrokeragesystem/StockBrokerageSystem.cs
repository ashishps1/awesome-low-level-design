class StockBrokerageSystem
{
    private static volatile StockBrokerageSystem instance;
    private static readonly object syncRoot = new object();
    private readonly Dictionary<string, User> users;
    private readonly Dictionary<string, Stock> stocks;

    private StockBrokerageSystem()
    {
        this.users = new Dictionary<string, User>();
        this.stocks = new Dictionary<string, Stock>();
    }

    public static StockBrokerageSystem GetInstance()
    {
        if (instance == null)
        {
            lock (syncRoot)
            {
                if (instance == null)
                {
                    instance = new StockBrokerageSystem();
                }
            }
        }
        return instance;
    }

    public User RegisterUser(string name, double initialAmount)
    {
        var user = new User(name, initialAmount);
        users[user.GetUserId()] = user;
        return user;
    }

    public Stock AddStock(string symbol, double initialPrice)
    {
        var stock = new Stock(symbol, initialPrice);
        stocks[stock.GetSymbol()] = stock;
        return stock;
    }

    public void PlaceBuyOrder(Order order)
    {
        var user = order.GetUser();
        IOrderCommand command = new BuyStockCommand(user.GetAccount(), order);
        command.Execute();
    }

    public void PlaceSellOrder(Order order)
    {
        var user = order.GetUser();
        IOrderCommand command = new SellStockCommand(user.GetAccount(), order);
        command.Execute();
    }

    public void CancelOrder(Order order)
    {
        order.Cancel();
    }
}