package restaurantmanagementsystem.payment;

public class CreditCardPayment implements Payment{
    @Override
    public boolean processPayment(double amount) {
        System.out.println("Processing credit card payment for amount: " + amount);
        return true;
    }
}
