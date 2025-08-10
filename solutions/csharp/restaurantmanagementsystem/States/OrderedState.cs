class OrderedState : IOrderItemState
{
    public void Next(OrderItem item)
    {
        item.SetState(new PreparingState());
    }

    public void Prev(OrderItem item)
    {
        Console.WriteLine("This is the initial state.");
    }

    public string GetStatus() => "ORDERED";
}