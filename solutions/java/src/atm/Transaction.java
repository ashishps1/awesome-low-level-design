package atm;

public abstract class Transaction {
    protected final String transactionId;
    protected final Account account;
    protected final double amount;

    public Transaction(String transactionId, Account account, double amount) {
        this.transactionId = transactionId;
        this.account = account;
        this.amount = amount;
    }

    public abstract void execute();
}
