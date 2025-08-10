class Order
{
    private readonly string orderId;
    private readonly User user;
    private readonly Stock stock;
    private readonly OrderType type;
    private readonly int quantity;
    private readonly double price; // Limit price for Limit orders
    private OrderStatus status;
    private readonly User owner;
    private IOrderState currentState;
    private readonly IExecutionStrategy executionStrategy;

    public Order(string orderId, User user, Stock stock, OrderType type, int quantity, 
                 double price, IExecutionStrategy strategy, User owner)
    {
        this.orderId = orderId;
        this.user = user;
        this.stock = stock;
        this.type = type;
        this.quantity = quantity;
        this.price = price;
        this.executionStrategy = strategy;
        this.owner = owner;
        this.currentState = new OpenState(); // Initial state
        this.status = OrderStatus.OPEN;
    }

    public void Cancel()
    {
        currentState.Cancel(this);
    }

    // Getters
    public string GetOrderId() { return orderId; }
    public User GetUser() { return user; }
    public Stock GetStock() { return stock; }
    public OrderType GetOrderType() { return type; }
    public int GetQuantity() { return quantity; }
    public double GetPrice() { return price; }
    public OrderStatus GetStatus() { return status; }
    public IExecutionStrategy GetExecutionStrategy() { return executionStrategy; }

    // Setters for state transitions
    public void SetState(IOrderState state)
    {
        this.currentState = state;
    }

    public void SetStatus(OrderStatus status)
    {
        this.status = status;
        NotifyOwner();
    }

    private void NotifyOwner()
    {
        if (owner != null)
        {
            owner.OrderStatusUpdate(this);
        }
    }
}