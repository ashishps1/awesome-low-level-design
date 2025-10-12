class PrepareOrderCommand : ICommand
{
    private readonly Order order;
    private readonly Chef chef;

    public PrepareOrderCommand(Order order, Chef chef)
    {
        this.order = order;
        this.chef = chef;
    }

    public void Execute()
    {
        chef.PrepareOrder(order);
    }
}