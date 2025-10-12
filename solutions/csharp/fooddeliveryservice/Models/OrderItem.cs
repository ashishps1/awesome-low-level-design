class OrderItem
{
    private readonly MenuItem item;
    private readonly int quantity;

    public OrderItem(MenuItem item, int quantity)
    {
        this.item = item;
        this.quantity = quantity;
    }

    public MenuItem GetItem() { return item; }
    public int GetQuantity() { return quantity; }
}