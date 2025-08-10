class ServeOrderCommand : ICommand
{
    private readonly Order order;
    private readonly Waiter waiter;

    public ServeOrderCommand(Order order, Waiter waiter)
    {
        this.order = order;
        this.waiter = waiter;
    }

    public void Execute()
    {
        waiter.ServeOrder(order);
    }
}