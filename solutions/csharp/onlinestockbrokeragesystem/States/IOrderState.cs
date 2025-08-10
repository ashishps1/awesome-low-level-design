interface IOrderState
{
    void Handle(Order order);
    void Cancel(Order order);
}