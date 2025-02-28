namespace AirlineManagementSystem
{
    public class Payment
    {
        public string PaymentId { get; }
        public string PaymentMethod { get; }
        public double Amount { get; }
        public PaymentStatus Status { get; private set; }

        public Payment(string paymentId, string paymentMethod, double amount)
        {
            PaymentId = paymentId;
            PaymentMethod = paymentMethod;
            Amount = amount;
            Status = PaymentStatus.PENDING;
        }

        public void ProcessPayment()
        {
            // Process payment logic here
            Status = PaymentStatus.COMPLETED;
        }
    }
}