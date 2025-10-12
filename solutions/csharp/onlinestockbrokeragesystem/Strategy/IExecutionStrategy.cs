interface IExecutionStrategy
{
    bool CanExecute(Order order, double marketPrice);
}