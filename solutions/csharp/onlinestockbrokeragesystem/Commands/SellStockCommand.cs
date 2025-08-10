class SellStockCommand : IOrderCommand
{
    private readonly Account account;
    private readonly Order order;
    private readonly StockExchange stockExchange;

    public SellStockCommand(Account account, Order order)
    {
        this.account = account;
        this.order = order;
        this.stockExchange = StockExchange.GetInstance();
    }

    public void Execute()
    {
        if (account.GetStockQuantity(order.GetStock().GetSymbol()) < order.GetQuantity())
        {
            throw new InsufficientStockException("Not enough stock to place sell order.");
        }
        Console.WriteLine($"Placing SELL order {order.GetOrderId()} for {order.GetQuantity()} shares of {order.GetStock().GetSymbol()}.");
        stockExchange.PlaceSellOrder(order);
    }
}