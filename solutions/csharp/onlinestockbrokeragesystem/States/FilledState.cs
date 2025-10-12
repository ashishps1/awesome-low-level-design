class FilledState : IOrderState
{
    public void Handle(Order order)
    {
        Console.WriteLine("Order is already filled.");
    }

    public void Cancel(Order order)
    {
        Console.WriteLine("Cannot cancel a filled order.");
    }
}