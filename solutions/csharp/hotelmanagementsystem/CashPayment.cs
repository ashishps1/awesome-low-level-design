namespace HotelManagement
{
    public class CashPayment : Payment
    {
        public bool ProcessPayment(double amount)
        {
            // Process cash payment
            return true;
        }
    }
}