class Restaurant
{
    private static Restaurant instance;
    private static readonly object lockObject = new object();
    private readonly Dictionary<string, Waiter> waiters = new Dictionary<string, Waiter>();
    private readonly Dictionary<string, Chef> chefs = new Dictionary<string, Chef>();
    private readonly Dictionary<int, Table> tables = new Dictionary<int, Table>();
    private readonly Menu menu = new Menu();

    private Restaurant() { }

    public static Restaurant GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new Restaurant();
                }
            }
        }
        return instance;
    }

    public void AddWaiter(Waiter waiter) => waiters[waiter.GetId()] = waiter;
    public Waiter GetWaiter(string id) => waiters.TryGetValue(id, out Waiter waiter) ? waiter : null;

    public void AddChef(Chef chef) => chefs[chef.GetId()] = chef;
    public Chef GetChef(string id) => chefs.TryGetValue(id, out Chef chef) ? chef : null;

    public List<Chef> GetChefs() => chefs.Values.ToList();
    public List<Waiter> GetWaiters() => waiters.Values.ToList();

    public void AddTable(Table table) => tables[table.GetId()] = table;
    public Menu GetMenu() => menu;
}