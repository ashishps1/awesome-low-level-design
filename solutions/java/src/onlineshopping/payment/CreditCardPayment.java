package onlineshopping.payment;

public class CreditCardPayment implements Payment {
    @Override
    public boolean processPayment(double amount) {
        // Process credit card payment
        return true;
    }
}
