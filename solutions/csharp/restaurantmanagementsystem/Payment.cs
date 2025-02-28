namespace RestaurantManagementSystem
{
    public class Payment
    {
        public int Id { get; }
        public double Amount { get; }
        public PaymentMethod Method { get; }
        public PaymentStatus Status { get; }

        public Payment(int id, double amount, PaymentMethod method, PaymentStatus status)
        {
            Id = id;
            Amount = amount;
            Method = method;
            Status = status;
        }
    }
}