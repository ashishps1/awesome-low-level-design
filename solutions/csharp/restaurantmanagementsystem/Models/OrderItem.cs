class OrderItem
{
    private readonly MenuItem menuItem;
    private readonly Order order;
    private IOrderItemState state;
    private readonly List<IOrderObserver> observers = new List<IOrderObserver>();

    public OrderItem(MenuItem menuItem, Order order)
    {
        this.menuItem = menuItem;
        this.order = order;
        this.state = new OrderedState();
    }

    public void ChangeState(IOrderItemState newState)
    {
        this.state = newState;
        Console.WriteLine($"Item '{menuItem.GetName()}' state changed to: {newState.GetStatus()}");
    }

    public void NextState()
    {
        state.Next(this);
    }

    public void SetState(IOrderItemState state)
    {
        this.state = state;
    }

    public void AddObserver(IOrderObserver observer)
    {
        observers.Add(observer);
    }

    public void NotifyObservers()
    {
        foreach (var observer in observers.ToList())
        {
            observer.Update(this);
        }
    }

    public MenuItem GetMenuItem() => menuItem;
    public Order GetOrder() => order;
}