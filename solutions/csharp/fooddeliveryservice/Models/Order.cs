class Order
{
    private readonly string id;
    private readonly Customer customer;
    private readonly Restaurant restaurant;
    private readonly List<OrderItem> items;
    private OrderStatus status;
    private DeliveryAgent deliveryAgent;
    private readonly List<IOrderObserver> observers = new List<IOrderObserver>();

    public Order(Customer customer, Restaurant restaurant, List<OrderItem> items)
    {
        this.id = Guid.NewGuid().ToString();
        this.customer = customer;
        this.restaurant = restaurant;
        this.items = items;
        this.status = OrderStatus.PENDING;
        AddObserver(customer);
        AddObserver(restaurant);
    }

    public void AddObserver(IOrderObserver observer)
    {
        observers.Add(observer);
    }

    private void NotifyObservers()
    {
        foreach (var observer in observers)
        {
            observer.OnUpdate(this);
        }
    }

    public void SetStatus(OrderStatus newStatus)
    {
        if (status != newStatus)
        {
            status = newStatus;
            NotifyObservers();
        }
    }

    public bool Cancel()
    {
        if (status == OrderStatus.PENDING)
        {
            SetStatus(OrderStatus.CANCELLED);
            return true;
        }
        return false;
    }

    public void AssignDeliveryAgent(DeliveryAgent agent)
    {
        deliveryAgent = agent;
        AddObserver(agent);
        agent.SetAvailable(false);
    }

    public string GetId() { return id; }
    public OrderStatus GetStatus() { return status; }
    public Customer GetCustomer() { return customer; }
    public Restaurant GetRestaurant() { return restaurant; }
    public DeliveryAgent GetDeliveryAgent() { return deliveryAgent; }
}