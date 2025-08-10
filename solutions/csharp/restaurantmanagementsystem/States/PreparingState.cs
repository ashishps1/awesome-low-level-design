class PreparingState : IOrderItemState
{
    public void Next(OrderItem item)
    {
        item.SetState(new ReadyForPickupState());
    }

    public void Prev(OrderItem item)
    {
        item.SetState(new OrderedState());
    }

    public string GetStatus() => "PREPARING";
}