public class StrategyPatternDemo {
    public static void main(String[] args) {
        ShoppingCart cart = new ShoppingCart();

        // Pay by credit card
        cart.setPaymentStrategy(new CreditCardPayment("John Doe", "1234567890123456", "786", "12/25"));
        cart.checkout(100);

        // Pay by PayPal
        cart.setPaymentStrategy(new PayPalPayment("johndoe@example.com", "mypwd"));
        cart.checkout(200);

        // Pay by Bitcoin
        cart.setPaymentStrategy(new BitcoinPayment("1BvBMSEYstWetqTFn5Au4m4GFg7xJaNVN2"));
        cart.checkout(300);
    }
}
