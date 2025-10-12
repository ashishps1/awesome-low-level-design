class Chef : Staff
{
    public Chef(string id, string name) : base(id, name) { }

    public void PrepareOrder(Order order)
    {
        Console.WriteLine($"Chef {name} received order {order.GetOrderId()} and is starting preparation.");
        foreach (var item in order.GetOrderItems())
        {
            item.ChangeState(new PreparingState());
        }
    }
}