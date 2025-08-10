class CancelledState : IOrderState
{
    public void Ship(Order order)
    {
        Console.WriteLine("Cannot ship a cancelled order.");
    }

    public void Deliver(Order order)
    {
        Console.WriteLine("Cannot deliver a cancelled order.");
    }

    public void Cancel(Order order)
    {
        Console.WriteLine("Order is already cancelled.");
    }
}