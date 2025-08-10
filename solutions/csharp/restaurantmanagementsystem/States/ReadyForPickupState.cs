class ReadyForPickupState : IOrderItemState
{
    public void Next(OrderItem item)
    {
        item.NotifyObservers();
    }

    public void Prev(OrderItem item)
    {
        item.SetState(new PreparingState());
    }

    public string GetStatus() => "READY_FOR_PICKUP";
}