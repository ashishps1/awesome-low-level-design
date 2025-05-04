package coffeevendingmachine;

public class PaymentProcessor {
    public double process(double price, double paid) {
        System.out.println("Processing Payment...");
        return paid - price;
    }
}
