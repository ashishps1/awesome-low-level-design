class Waiter : Staff, IOrderObserver
{
    public Waiter(string id, string name) : base(id, name) { }

    public void ServeOrder(Order order)
    {
        Console.WriteLine($"Waiter {name} is serving order {order.GetOrderId()}");
        foreach (var item in order.GetOrderItems())
        {
            item.ChangeState(new ServedState());
        }
    }

    public void Update(OrderItem item)
    {
        Console.WriteLine($">>> WAITER {name} NOTIFIED: Item '{item.GetMenuItem().GetName()}' " +
                         $"for table {item.GetOrder().GetTableId()} is READY FOR PICKUP.");
    }
}