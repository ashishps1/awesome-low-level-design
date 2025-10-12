interface IOrderState
{
    void Ship(Order order);
    void Deliver(Order order);
    void Cancel(Order order);
}