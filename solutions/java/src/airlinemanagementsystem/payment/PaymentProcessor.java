package airlinemanagementsystem.payment;

public class PaymentProcessor {
    private static PaymentProcessor instance;

    private PaymentProcessor() {
    }

    public static synchronized PaymentProcessor getInstance() {
        if (instance == null) {
            instance = new PaymentProcessor();
        }
        return instance;
    }

    public void processPayment(Payment payment) {
        // Process payment using the selected payment method
        payment.processPayment();
    }
}
