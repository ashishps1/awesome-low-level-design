class DeliveredState : IOrderState
{
    public void Ship(Order order)
    {
        Console.WriteLine("Order already delivered.");
    }

    public void Deliver(Order order)
    {
        Console.WriteLine("Order already delivered.");
    }

    public void Cancel(Order order)
    {
        Console.WriteLine("Cannot cancel a delivered order.");
    }
}