package onlinestockbrokeragesystem;

public class BuyOrder extends Order {
    public BuyOrder(String orderId, Account account, Stock stock, int quantity, double price) {
        super(orderId, account, stock, quantity, price);
    }

    @Override
    public void execute() {
        double totalCost = quantity * price;
        if (account.getBalance() >= totalCost) {
            account.withdraw(totalCost);
            // Update portfolio and perform necessary actions
            account.getPortfolio().addStock(stock, quantity);
            status = OrderStatus.EXECUTED;
        } else {
            status = OrderStatus.REJECTED;
            throw new InsufficientFundsException("Insufficient funds to execute the buy order.");
        }
    }
}
