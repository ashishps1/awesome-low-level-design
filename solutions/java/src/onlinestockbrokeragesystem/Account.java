package onlinestockbrokeragesystem;

public class Account {
    private final String accountId;
    private final User user;
    private double balance;
    private final Portfolio portfolio;

    public Account(String accountId, User user, double initialBalance) {
        this.accountId = accountId;
        this.user = user;
        this.balance = initialBalance;
        this.portfolio = new Portfolio(this);
    }

    public synchronized void deposit(double amount) {
        balance += amount;
    }

    public synchronized void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
        } else {
            throw new InsufficientFundsException("Insufficient funds in the account.");
        }
    }

    public String getAccountId() {
        return accountId;
    }

    public User getUser() {
        return user;
    }

    public double getBalance() {
        return balance;
    }

    public Portfolio getPortfolio() {
        return portfolio;
    }
}
