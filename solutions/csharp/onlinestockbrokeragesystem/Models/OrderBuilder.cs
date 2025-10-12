class OrderBuilder
{
    private User user;
    private Stock stock;
    private OrderType type;
    private TransactionType transactionType;
    private int quantity;
    private double price;

    public OrderBuilder ForUser(User user)
    {
        this.user = user;
        return this;
    }

    public OrderBuilder WithStock(Stock stock)
    {
        this.stock = stock;
        return this;
    }

    public OrderBuilder Buy(int quantity)
    {
        this.transactionType = TransactionType.BUY;
        this.quantity = quantity;
        return this;
    }

    public OrderBuilder Sell(int quantity)
    {
        this.transactionType = TransactionType.SELL;
        this.quantity = quantity;
        return this;
    }

    public OrderBuilder AtMarketPrice()
    {
        this.type = OrderType.MARKET;
        this.price = 0; // Not needed for market order
        return this;
    }

    public OrderBuilder WithLimit(double limitPrice)
    {
        this.type = OrderType.LIMIT;
        this.price = limitPrice;
        return this;
    }

    public Order Build()
    {
        IExecutionStrategy strategy = type == OrderType.MARKET ? 
            (IExecutionStrategy) new MarketOrderStrategy() : 
            (IExecutionStrategy) new LimitOrderStrategy(transactionType);
        
        return new Order(
            Guid.NewGuid().ToString(),
            user,
            stock,
            type,
            quantity,
            price,
            strategy,
            user
        );
    }
}