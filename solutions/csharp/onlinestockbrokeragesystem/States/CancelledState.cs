class CancelledState : IOrderState
{
    public void Handle(Order order)
    {
        Console.WriteLine("Order is cancelled.");
    }

    public void Cancel(Order order)
    {
        Console.WriteLine("Order is already cancelled.");
    }
}