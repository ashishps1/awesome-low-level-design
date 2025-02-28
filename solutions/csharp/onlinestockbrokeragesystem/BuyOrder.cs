namespace OnlineStockBrokerageSystem
{
    public class BuyOrder : Order
    {
        public BuyOrder(string orderId, Account account, Stock stock, int quantity, double price)
            : base(orderId, account, stock, quantity, price)
        {
        }

        public override void Execute()
        {
            var totalCost = Quantity * Price;
            if (Account.GetBalance() >= totalCost)
            {
                Account.Withdraw(totalCost);
                Account.Portfolio.AddStock(Stock, Quantity);
                Status = OrderStatus.Executed;
            }
            else
            {
                Status = OrderStatus.Rejected;
                throw new InsufficientFundsException("Insufficient funds to execute the buy order.");
            }
        }
    }
}