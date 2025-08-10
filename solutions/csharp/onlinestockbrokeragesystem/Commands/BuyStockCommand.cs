class BuyStockCommand : IOrderCommand
{
    private readonly Account account;
    private readonly Order order;
    private readonly StockExchange stockExchange;

    public BuyStockCommand(Account account, Order order)
    {
        this.account = account;
        this.order = order;
        this.stockExchange = StockExchange.GetInstance();
    }

    public void Execute()
    {
        double estimatedCost = order.GetQuantity() * order.GetPrice();
        if (order.GetOrderType() == OrderType.LIMIT && account.GetBalance() < estimatedCost)
        {
            throw new InsufficientFundsException("Not enough cash to place limit buy order.");
        }
        Console.WriteLine($"Placing BUY order {order.GetOrderId()} for {order.GetQuantity()} shares of {order.GetStock().GetSymbol()}.");
        stockExchange.PlaceBuyOrder(order);
    }
}