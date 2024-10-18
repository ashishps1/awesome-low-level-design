namespace HotelManagement
{
    public class CreditCardPayment : Payment
    {
        public bool ProcessPayment(double amount)
        {
            // Process credit card payment
            return true;
        }
    }
}