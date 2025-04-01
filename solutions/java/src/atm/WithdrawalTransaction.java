package atm;

public class WithdrawalTransaction extends Transaction {
    public WithdrawalTransaction(String transactionId, Account account, double amount) {
        super(transactionId, account, amount);
    }

    @Override
    public void execute() {
        account.debit(amount);
    }
}
