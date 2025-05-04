package onlineshoppingservice.payment;

public class CreditCardPayment implements Payment {
    @Override
    public boolean processPayment(double amount) {
        // Process credit card payment
        System.out.println("Processing credit card payment for amount: " + amount);
        return true;
    }
}
