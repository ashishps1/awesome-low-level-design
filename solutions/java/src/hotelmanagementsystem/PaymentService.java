package hotelmanagementsystem;

public class PaymentService {
    public boolean processPayment(double amount) {
        System.out.println("Processing payment of $" + String.format("%.2f", amount) + "...");
        // In a real system, this would interact with a payment gateway
        System.out.println("Payment successful.");
        return true;
    }
}
