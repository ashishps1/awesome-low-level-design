class OpenState : IOrderState
{
    public void Handle(Order order)
    {
        Console.WriteLine("Order is open and waiting for execution.");
    }

    public void Cancel(Order order)
    {
        order.SetStatus(OrderStatus.CANCELLED);
        order.SetState(new CancelledState());
        Console.WriteLine($"Order {order.GetOrderId()} has been cancelled.");
    }
}