namespace OnlineStockBrokerageSystem
{
    public class SellOrder : Order
    {
        public SellOrder(string orderId, Account account, Stock stock, int quantity, double price)
            : base(orderId, account, stock, quantity, price)
        {
        }

        public override void Execute()
        {
            Account.Portfolio.RemoveStock(Stock, Quantity);
            var totalProceeds = Quantity * Price;
            Account.Deposit(totalProceeds);
            Status = OrderStatus.Executed;
        }
    }
}