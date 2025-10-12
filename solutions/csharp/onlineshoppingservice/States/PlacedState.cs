class PlacedState : IOrderState
{
    public void Ship(Order order)
    {
        Console.WriteLine($"Shipping order {order.GetId()}");
        order.SetStatus(OrderStatus.SHIPPED);
        order.SetState(new ShippedState());
    }

    public void Deliver(Order order)
    {
        Console.WriteLine("Cannot deliver an order that has not been shipped.");
    }

    public void Cancel(Order order)
    {
        Console.WriteLine($"Cancelling order {order.GetId()}");
        order.SetStatus(OrderStatus.CANCELLED);
        order.SetState(new CancelledState());
    }
}