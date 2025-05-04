package restaurantmanagementsystem.payment;

public class CashPayment implements Payment{
    @Override
    public boolean processPayment(double amount) {
        System.out.println("Paid using Cash for amount: " + amount);
        return true;
    }
}
