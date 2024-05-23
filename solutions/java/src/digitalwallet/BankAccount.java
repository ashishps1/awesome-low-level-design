package digitalwallet;

import java.math.BigDecimal;

public class BankAccount extends PaymentMethod {
    private final String accountNumber;
    private final String routingNumber;

    public BankAccount(String id, User user, String accountNumber, String routingNumber) {
        super(id, user);
        this.accountNumber = accountNumber;
        this.routingNumber = routingNumber;
    }

    @Override
    public boolean processPayment(BigDecimal amount, Currency currency) {
        // Process bank account payment
        return true;
    }
}