package digitalwallet;

import java.math.BigDecimal;

public abstract class PaymentMethod {
    protected final String id;
    protected final User user;

    public PaymentMethod(String id, User user) {
        this.id = id;
        this.user = user;
    }

    public abstract boolean processPayment(BigDecimal amount, Currency currency);

    public String getId() {
        return id;
    }

    public User getUser() {
        return user;
    }
}
