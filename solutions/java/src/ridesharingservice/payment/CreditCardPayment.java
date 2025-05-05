package ridesharingservice.payment;

public class CreditCardPayment implements Payment{
    @Override
    public void processPayment(double amount) {
        System.out.println("Processing payment using credit card for amount: " + amount);
    }
}
