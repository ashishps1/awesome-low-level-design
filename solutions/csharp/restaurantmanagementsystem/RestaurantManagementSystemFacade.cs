class RestaurantManagementSystemFacade
{
    private static RestaurantManagementSystemFacade instance;
    private static readonly object lockObject = new object();
    private readonly Restaurant restaurant = Restaurant.GetInstance();
    private int orderIdCounter = 1;
    private readonly Dictionary<int, Order> orders = new Dictionary<int, Order>();

    private RestaurantManagementSystemFacade() { }

    public static RestaurantManagementSystemFacade GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new RestaurantManagementSystemFacade();
                }
            }
        }
        return instance;
    }

    public Table AddTable(int id, int capacity)
    {
        Table table = new Table(id, capacity);
        restaurant.AddTable(table);
        return table;
    }

    public Waiter AddWaiter(string id, string name)
    {
        Waiter waiter = new Waiter(id, name);
        restaurant.AddWaiter(waiter);
        return waiter;
    }

    public Chef AddChef(string id, string name)
    {
        Chef chef = new Chef(id, name);
        restaurant.AddChef(chef);
        return chef;
    }

    public MenuItem AddMenuItem(string id, string name, double price)
    {
        MenuItem item = new MenuItem(id, name, price);
        restaurant.GetMenu().AddItem(item);
        return item;
    }

    public Order TakeOrder(int tableId, string waiterId, List<string> menuItemIds)
    {
        Waiter waiter = restaurant.GetWaiter(waiterId);
        if (waiter == null)
        {
            throw new ArgumentException("Invalid waiter ID.");
        }

        var chefs = restaurant.GetChefs();
        if (!chefs.Any())
        {
            throw new InvalidOperationException("No chefs available.");
        }
        Chef chef = chefs.First();

        Order order = new Order(Interlocked.Increment(ref orderIdCounter) - 1, tableId);
        foreach (string itemId in menuItemIds)
        {
            MenuItem menuItem = restaurant.GetMenu().GetItem(itemId);
            OrderItem orderItem = new OrderItem(menuItem, order);
            orderItem.AddObserver(waiter);
            order.AddItem(orderItem);
        }

        ICommand prepareOrderCommand = new PrepareOrderCommand(order, chef);
        prepareOrderCommand.Execute();

        orders[order.GetOrderId()] = order;
        return order;
    }

    public void MarkItemsAsReady(int orderId)
    {
        Order order = orders[orderId];
        Console.WriteLine($"\nChef has finished preparing order {order.GetOrderId()}");

        foreach (var item in order.GetOrderItems())
        {
            item.NextState();
            item.NextState();
        }
    }

    public void ServeOrder(string waiterId, int orderId)
    {
        Order order = orders[orderId];
        Waiter waiter = restaurant.GetWaiter(waiterId);

        ICommand serveOrderCommand = new ServeOrderCommand(order, waiter);
        serveOrderCommand.Execute();
    }

    public Bill GenerateBill(int orderId)
    {
        Order order = orders[orderId];
        IBillComponent billComponent = new BaseBill(order);
        billComponent = new TaxDecorator(billComponent, 0.08);
        billComponent = new ServiceChargeDecorator(billComponent, 5.00);

        return new Bill(billComponent);
    }
}