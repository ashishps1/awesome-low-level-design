class ShippedState : IOrderState
{
    public void Ship(Order order)
    {
        Console.WriteLine("Order is already shipped.");
    }

    public void Deliver(Order order)
    {
        Console.WriteLine($"Delivering order {order.GetId()}");
        order.SetStatus(OrderStatus.DELIVERED);
        order.SetState(new DeliveredState());
    }

    public void Cancel(Order order)
    {
        Console.WriteLine("Cannot cancel a shipped order.");
    }
}