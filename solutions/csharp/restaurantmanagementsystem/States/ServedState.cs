class ServedState : IOrderItemState
{
    public void Next(OrderItem item)
    {
        Console.WriteLine("This is the final state.");
    }

    public void Prev(OrderItem item)
    {
        Console.WriteLine("Cannot revert a served item.");
    }

    public string GetStatus() => "SERVED";
}