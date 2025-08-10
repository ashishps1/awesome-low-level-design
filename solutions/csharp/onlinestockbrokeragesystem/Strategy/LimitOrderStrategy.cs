class LimitOrderStrategy : IExecutionStrategy
{
    private readonly TransactionType type;

    public LimitOrderStrategy(TransactionType type)
    {
        this.type = type;
    }

    public bool CanExecute(Order order, double marketPrice)
    {
        if (type == TransactionType.BUY)
        {
            // Buy if market price is less than or equal to limit price
            return marketPrice <= order.GetPrice();
        }
        else // SELL
        {
            // Sell if market price is greater than or equal to limit price
            return marketPrice >= order.GetPrice();
        }
    }
}