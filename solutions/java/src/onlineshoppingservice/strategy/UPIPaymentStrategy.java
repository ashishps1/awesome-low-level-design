package onlineshoppingservice.strategy;

public class UPIPaymentStrategy implements PaymentStrategy{
    private final String upiId;

    public UPIPaymentStrategy(String upiId) { this.upiId = upiId; }

    @Override
    public boolean pay(double amount) {
        System.out.printf("Processing UPI payment of $%.2f with upi id %s.%n", amount, upiId);
        // Simulate payment gateway logic
        return true;
    }
}
