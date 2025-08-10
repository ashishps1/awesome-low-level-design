class Order
{
    private readonly int orderId;
    private readonly int tableId;
    private readonly List<OrderItem> items = new List<OrderItem>();

    public Order(int orderId, int tableId)
    {
        this.orderId = orderId;
        this.tableId = tableId;
    }

    public void AddItem(OrderItem item)
    {
        items.Add(item);
    }

    public double GetTotalPrice()
    {
        return items.Sum(item => item.GetMenuItem().GetPrice());
    }

    public int GetOrderId() => orderId;
    public int GetTableId() => tableId;
    public List<OrderItem> GetOrderItems() => items;
}