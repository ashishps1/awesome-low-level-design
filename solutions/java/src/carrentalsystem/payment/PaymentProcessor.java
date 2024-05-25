package carrentalsystem.payment;

public interface PaymentProcessor {
    boolean processPayment(double amount);
}
