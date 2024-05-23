package digitalwallet;

import java.math.BigDecimal;

public class CreditCard extends PaymentMethod {
    private final String cardNumber;
    private final String expirationDate;
    private final String cvv;

    public CreditCard(String id, User user, String cardNumber, String expirationDate, String cvv) {
        super(id, user);
        this.cardNumber = cardNumber;
        this.expirationDate = expirationDate;
        this.cvv = cvv;
    }

    @Override
    public boolean processPayment(BigDecimal amount, Currency currency) {
        // Process credit card payment
        return true;
    }
}
