class MarketOrderStrategy : IExecutionStrategy
{
    public bool CanExecute(Order order, double marketPrice)
    {
        return true; // Market orders can always execute
    }
}