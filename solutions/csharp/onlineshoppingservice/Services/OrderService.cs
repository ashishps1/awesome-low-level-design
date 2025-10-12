class OrderService
{
    private readonly InventoryService inventoryService;

    public OrderService(InventoryService inventoryService)
    {
        this.inventoryService = inventoryService;
    }

    public Order CreateOrder(Customer customer, ShoppingCart cart)
    {
        var orderItems = cart.GetItems().Values
            .Select(cartItem => new OrderLineItem(
                cartItem.GetProduct().GetId(),
                cartItem.GetProduct().GetName(),
                cartItem.GetQuantity(),
                cartItem.GetProduct().GetPrice()))
            .ToList();

        inventoryService.UpdateStockForOrder(orderItems);

        return new Order(customer, orderItems, customer.GetShippingAddress(), cart.CalculateTotal());
    }
}