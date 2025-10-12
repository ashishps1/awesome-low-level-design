class BaseBill : IBillComponent
{
    private readonly Order order;

    public BaseBill(Order order)
    {
        this.order = order;
    }

    public double CalculateTotal() => order.GetTotalPrice();
    public string GetDescription() => "Order Items";
}