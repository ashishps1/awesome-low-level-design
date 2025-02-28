namespace OnlineStockBrokerageSystem
{
    public abstract class Order
    {
        protected readonly string OrderId;
        protected readonly Account Account;
        protected readonly Stock Stock;
        protected readonly int Quantity;
        protected readonly double Price;
        protected OrderStatus Status;

        public Order(string orderId, Account account, Stock stock, int quantity, double price)
        {
            OrderId = orderId;
            Account = account;
            Stock = stock;
            Quantity = quantity;
            Price = price;
            Status = OrderStatus.Pending;
        }

        public abstract void Execute();
    }
}